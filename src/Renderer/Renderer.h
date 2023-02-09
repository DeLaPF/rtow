#pragma once

#include "Camera/Camera.h"
#include "Math/Ray.h"
#include "Scene/Scene.h"
#include "Scene/SceneComponent.h"
#include "Math/Vec3.h"

#include <cstdint>

class Renderer {
    public:
        Renderer() = default;

        void Resize(uint32_t width, uint32_t height);

        void Render(const Scene& scene, const Camera& camera);

    private:
        Vec3 RayGen(uint32_t x, uint32_t y);

        HitResult TraceRay(const Ray& ray);

    private:
        uint32_t m_ImageWidth;
        uint32_t m_ImageHeight;
        double m_AspectRatio;
        uint32_t m_Samples = 100;
        uint32_t* m_ImageData = nullptr;

        const Scene* m_ActiveScene = nullptr;
        const Camera* m_ActiveCamera = nullptr;
};
