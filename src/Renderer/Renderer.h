#pragma once

#include "Camera/Camera.h"
#include "Math/Ray.h"
#include "Math/Vec.h"
#include "Renderer/Image.h"
#include "Scene/Scene.h"

class Renderer {
    public:
        Renderer() : m_Samples(100), m_Bounces(50) {}
        Renderer(uint32_t samples, uint32_t bounces)
            : m_Samples(samples), m_Bounces(bounces) {}

        ~Renderer() { delete[] m_Image.Data; }

        void Resize(uint32_t width, uint32_t height);

        Image& Render(const Scene& scene, const Camera& camera);
    private:
        Vec3 RayGen(uint32_t x, uint32_t y);

        Vec3 TraceRay(const Ray& ray, uint32_t bounces);
    private:
        Image m_Image;
        uint32_t m_Samples;
        uint32_t m_Bounces;

        const Scene* m_ActiveScene = nullptr;
        const Camera* m_ActiveCamera = nullptr;
};
