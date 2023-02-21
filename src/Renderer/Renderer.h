#pragma once

#include "Image.h"
#include "Camera/Camera.h"
#include "Math/Ray.h"
#include "Math/Vec.h"
#include "Scene/Scene.h"

class Renderer {
    public:
        Renderer() = default;

        void Resize(uint32_t width, uint32_t height);

        Image& Render(const Scene& scene, const Camera& camera);
    private:
        Vec3 RayGen(uint32_t x, uint32_t y);

        Vec3 TraceRay(const Ray& ray, uint32_t bounces);
    private:
        Image m_Image;
        uint32_t m_Samples = 100;
        uint32_t m_Bounces = 50;

        const Scene* m_ActiveScene = nullptr;
        const Camera* m_ActiveCamera = nullptr;
};
