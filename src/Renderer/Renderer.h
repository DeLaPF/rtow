#pragma once

#include "Camera/Camera.h"
#include "Math/Ray.h"
#include "Scene/Scene.h"
#include "Scene/SceneComponent.h"
#include "Math/Vec3.h"

#include <cstdint>

struct Image {
    Vec3* Data;
    uint32_t Width;
    uint32_t Height;
    double AspectRatio;
};

class Renderer {
    public:
        Renderer() = default;

        void Resize(uint32_t width, uint32_t height);

        void Render(const Scene& scene, const Camera& camera);
    private:
        Vec3 RayGen(uint32_t x, uint32_t y);

        Vec3 TraceRay(const Ray& ray, uint32_t bounces);
    private:
        Image m_Image{nullptr, 0, 0, 0.0};
        uint32_t m_Samples = 100;
        uint32_t m_Bounces = 50;

        const Scene* m_ActiveScene = nullptr;
        const Camera* m_ActiveCamera = nullptr;
};
