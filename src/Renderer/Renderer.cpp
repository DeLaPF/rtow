#include "Renderer.h"

#include "Math/Random.h"
#include "Math/Utils.h"
#include "Scene/SceneComponent.h"

#include <cstdint>
#include <iostream>

namespace ColorUtils {
    void WriteColor(std::ostream &out, Vec3 color) {
        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(256 * Utils::clamp(color.X, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Utils::clamp(color.Y, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Utils::clamp(color.Z, 0.0, 0.999)) << '\n';
    }
}

void Renderer::Resize(uint32_t width, uint32_t height) {
    if (m_ImageWidth == width && m_ImageHeight == height) {
        return;
    }

    m_ImageWidth = width; 
    m_ImageHeight = height;
    m_AspectRatio = (double)width / height;

    delete[] m_ImageData;
    m_ImageData = new uint32_t[width * height];
}

void Renderer::Render(const Scene &scene, const Camera &camera) {
    m_ActiveScene = &scene;
    m_ActiveCamera = &camera;

    std::cout << "P3\n" << m_ImageWidth << ' ' << m_ImageHeight << "\n255\n";
    // TODO: test multithreading
    // (will need to store calculated data in temp array to maintain ordering)
    for (uint32_t y = 0; y < m_ImageHeight; y++) {
        std::cerr << "\rScanlines remaining: " << m_ImageHeight - 1 - y << ' ' << std::flush;
        for (uint32_t x = 0; x < m_ImageWidth; x++) {
            Vec3 color = RayGen(x, m_ImageHeight - y);
            ColorUtils::WriteColor(std::cout, color);
        }
    }
    std::cerr << "\nDone.\n";
}

Vec3 Renderer::RayGen(uint32_t x, uint32_t y) {
    Vec3 color = Vec3();

    for (uint32_t i = 0; i < m_Samples; i++) {
        // u: -1 to aspectRatio, v: -1 to 1
        double u = (2.0 * (double(x + RandomDouble()) / (m_ImageWidth - 1)) - 1.0) * m_AspectRatio;
        double v = 2.0 * (double(y + RandomDouble()) / (m_ImageHeight)) - 1.0;
        Vec3 direction = Vec3(u, v, -m_ActiveCamera->FocalLength);

        Ray ray = Ray(m_ActiveCamera->Origin, direction);
        HitResult res = m_ActiveScene->RayCast(ray, 0.0, std::numeric_limits<double>::infinity());
        if (!res.DidHit) { // Miss
            Vec3 direction = normalize(ray.Direction);
            double t = 0.5 * (direction.Y + 1.0);
            color += ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0)); //Lerp
        } else {
            color += 0.5 * (res.WorldNormal + Vec3(1.0, 1.0, 1.0));
        }
    }

    return color / m_Samples;
}
