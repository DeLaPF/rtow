#pragma once

#include "Camera/Camera.h"
#include "Math/Ray.h"
#include "Math/Vec.h"
#include "Renderer/Image.h"
#include "Scene/Scene.h"

class Renderer {
public:
    Renderer(uint32_t samples = 100, uint32_t bounces = 50)
        : m_BackgroundColor(Vec3()), m_Samples(samples), m_Bounces(bounces) {}

    ~Renderer() { delete[] m_Image.Data; }

    void Resize(uint32_t width, uint32_t height);

    Image& Render(const Scene& scene, const Camera& camera);

    void SetBackgroundColor(Vec3 backgroundColor) { m_BackgroundColor = backgroundColor; }
private:
    Vec3 RayGen(uint32_t x, uint32_t y);

    Vec3 TraceRay(const Ray& ray, uint32_t bounces);
private:
    Vec3 m_BackgroundColor;

    Image m_Image;
    uint32_t m_Samples;
    uint32_t m_Bounces;

    const Scene* m_ActiveScene = nullptr;
    const Camera* m_ActiveCamera = nullptr;
};
