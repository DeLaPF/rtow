#include "Renderer.h"

#include <atomic>
#include <iostream>
#include <thread>

void Renderer::Resize(uint32_t width, uint32_t height) {
    if (m_Image.Width == width && m_Image.Height == height) { return; }

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
        color += TraceRay(m_ActiveCamera->GetRay(x, y), 0) / m_Samples;
    }

    return color;
}

Vec3 Renderer::TraceRay(const Ray& ray, uint32_t bounces) {
    if (bounces >= m_Bounces) {
        return Vec3();
    }

    TraceResult res;
    if (!m_ActiveScene->RayCast(ray, 0.0001, std::numeric_limits<double>::infinity(), res)) { // Miss
        Vec3 direction = Vec3::normalize(ray.Direction);
        double t = 0.5 * (direction.Y + 1.0);
        return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0)); //Lerp
    }

    const auto hitComponent = m_ActiveScene->GetTraceableComponentAt(res.HitComponentIndex);
    const auto& hitMaterial = m_ActiveScene->GetMaterial(hitComponent->GetMaterialIndex());
    Ray bounced = Ray(res.WorldLocation, hitMaterial->GetBounce(ray.Direction, res.WorldNormal, res.IsFrontFace));

    return hitMaterial->Albedo(res.ComponentUV, res.WorldLocation) * TraceRay(bounced, ++bounces);
}
