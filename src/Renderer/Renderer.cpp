#include "Renderer.h"

#include "Math/Random.h"
#include "Math/Utils.h"
#include "Scene/SceneComponent.h"

#include <cstdint>
#include <execution>
#include <iostream>

namespace ImageUtils {
    void WriteColor(std::ostream &out, Vec3 color) {
        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(256 * Utils::clamp(color.X, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Utils::clamp(color.Y, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Utils::clamp(color.Z, 0.0, 0.999)) << '\n';
    }

    void OutputImage(std::ostream &out, const Image& image) {
        out << "P3\n" << image.Width << ' ' << image.Height << "\n255\n";
        for (uint32_t y = 0; y < image.Height; y++) {
            for (uint32_t x = 0; x < image.Width; x++) {
                ImageUtils::WriteColor(out, image.Data[(y * image.Width) + x]);
            }
        }
    }
}

void Renderer::Resize(uint32_t width, uint32_t height) {
    if (m_Image.Width == width && m_Image.Height == height) {
        return;
    }

    delete[] m_Image.Data;
    m_Image.Data = new Vec3[width * height];
    m_Image.Width = width;
    m_Image.Height = height;
    m_Image.AspectRatio = (double)width / height;
    m_Image.HorizontalIter.resize(width);
    m_Image.VerticalIter.resize(height);
    for (uint32_t i = 0; i < width; i++)
        m_Image.HorizontalIter[i] = i;
    for (uint32_t i = 0; i < height; i++)
        m_Image.VerticalIter[i] = i;

}

void Renderer::Render(const Scene &scene, const Camera &camera) {
    m_ActiveScene = &scene;
    m_ActiveCamera = &camera;

#define MT 1
#if MT
    std::for_each(std::execution::par, m_Image.VerticalIter.begin(), m_Image.VerticalIter.end(),
    [this](uint32_t y)
    {
        std::for_each(std::execution::par, m_Image.HorizontalIter.begin(), m_Image.HorizontalIter.end(),
        [this, y](uint32_t x)
        {
            Vec3 color = RayGen(x, m_Image.Height - y);
            m_Image.Data[(y * m_Image.Width) + x] = color;
        });
    });
#else
    for (uint32_t y = 0; y < m_Image.Height; y++) {
        std::cerr << "\rScanlines remaining: " << m_Image.Height - 1 - y << ' ' << std::flush;
        for (uint32_t x = 0; x < m_Image.Width; x++) {
            Vec3 color = RayGen(x, m_Image.Height - y);
            m_Image.Data[(y * m_Image.Width) + x] = color;
        }
    }
#endif

    ImageUtils::OutputImage(std::cout, m_Image);
    std::cerr << "\nDone.\n";
}

Vec3 Renderer::RayGen(uint32_t x, uint32_t y) {
    Vec3 color = Vec3();

    for (uint32_t i = 0; i < m_Samples; i++) {
        // u: -1 to aspectRatio, v: -1 to 1
        double u = (2.0 * (double(x + RandomDouble()) / (m_Image.Width - 1)) - 1.0) * m_Image.AspectRatio;
        double v = 2.0 * (double(y + RandomDouble()) / (m_Image.Height)) - 1.0;
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
