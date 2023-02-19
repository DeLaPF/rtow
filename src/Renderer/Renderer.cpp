#include "Renderer.h"

#include "Math/Random.h"

#include <atomic>
#include <thread>

namespace ImageUtils {
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
}

Image& Renderer::Render(const Scene &scene, const Camera &camera) {
    m_ActiveScene = &scene;
    m_ActiveCamera = &camera;

    static std::atomic_int progress = 0;
    std::vector<std::thread> threads;
    for (uint32_t y = 0; y < m_Image.Height; y++) {
        threads.push_back(std::thread([this, y]() -> void {
            for (uint32_t x = 0; x < m_Image.Width; x++) {
                m_Image.Data[(y * m_Image.Width) + x] = RayGen(x, y);
            }
            std::cerr << "\rScanlines remaining: " << m_Image.Height - ++progress << " " << std::flush;
        }));
    }
    for (auto& thread : threads) {
        thread.join();
    }

    return m_Image;
}

Vec3 Renderer::RayGen(uint32_t x, uint32_t y) {
    Vec3 color = Vec3();
    for (uint32_t i = 0; i < m_Samples; i++) {
        // u: -1 to aspectRatio (left to right), v: -1 to 1 (top to bottom)
        double u = (2.0 * ((x + Random::Double()) / (m_Image.Width - 1.0)) - 1.0) * m_Image.AspectRatio;
        double v = 2.0 * ((m_Image.Height - y + Random::Double()) / m_Image.Height) - 1.0;
        Ray ray = Ray(m_ActiveCamera->Origin, Vec3(u, v, -m_ActiveCamera->FocalLength));

        color += TraceRay(ray, 0) / m_Samples;
    }

    return color;
}

Vec3 Renderer::TraceRay(const Ray& ray, uint32_t bounces) {
    if (bounces >= m_Bounces) {
        return Vec3();
    }

    HitResult res = m_ActiveScene->RayCast(ray, 0.0001, std::numeric_limits<double>::infinity());
    if (!res.DidHit) { // Miss
        Vec3 direction = Vec3Util::normalize(ray.Direction);
        double t = 0.5 * (direction.Y + 1.0);
        return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0)); //Lerp
    }

    const auto& hitComponent = m_ActiveScene->GetComponent(res.HitIndex);
    const auto& hitMaterial = m_ActiveScene->GetMaterial(hitComponent->GetMaterialIndex());
    Ray bounced = Ray(res.WorldLocation, hitMaterial->GetBounce(ray.Direction, res.WorldNormal, res.IsFrontFace));

    return hitMaterial->Albedo * TraceRay(bounced, ++bounces);
}
