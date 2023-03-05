#pragma once

#include "Camera/Camera.h"
#include "Math/Ray.h"
#include "Math/Vec.h"
#include "Renderer/Image.h"
#include "Scene/Scene.h"

class Renderer {
public:
    Renderer() : m_BackgroundColor(Vec3()), m_SamplesPerPixel(100), m_MaxBounces(50) {}
    ~Renderer() { delete[] m_Image.Data; }

    void Resize(uint32_t width, uint32_t height);

    Image& Render(const Scene& scene, const Camera& camera);

    void SetBackgroundColor(Vec3 backgroundColor) { m_BackgroundColor = backgroundColor; }

    void SetSamplesPerPixel(uint32_t samplesPerPixel) { m_SamplesPerPixel = samplesPerPixel; }

    void SetMaxBounces(uint32_t maxBounces) { m_MaxBounces = maxBounces; }
private:
    Vec3 RayGen(uint32_t x, uint32_t y);

    Vec3 TraceRay(const Ray& ray, uint32_t bounces);
private:
    Vec3 m_BackgroundColor;

    Image m_Image;
    uint32_t m_SamplesPerPixel;
    uint32_t m_MaxBounces;

    const Scene* m_ActiveScene = nullptr;
    const Camera* m_ActiveCamera = nullptr;
};
