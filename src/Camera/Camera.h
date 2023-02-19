#pragma once

#include "Math/Ray.h"
#include "Math/Utils.h"
#include "Math/Vec3.h"
#include <cstdint>

class Camera {
    public:
        Camera() {}

        void Resize(uint32_t width, uint32_t height) {
            if (width == m_ViewportWidth && height == m_ViewportHeight) {
                return;
            }

            m_ViewportWidth = width;
            m_ViewportHeight = height;
            m_ViewportAspectRatio = (double)width / height;
        }

        void SetFOV(double fov) { m_FOV = fov; }

        void SetView(const Vec3& location, const Vec3& lookAt) {
            m_Origin = location;
            m_ViewDir = Vec3Util::normalize(location - lookAt);
            m_Right = Vec3Util::normalize(Vec3Util::cross(m_Up, m_ViewDir));
            m_LocalUp = Vec3Util::cross(m_ViewDir, m_Right);
        }

        Ray GetRay(uint32_t x, uint32_t y) const {
            double theta = Utils::degreesToRadians(m_FOV);
            double fovMul = std::tan(theta / 2);
            // u: -1 to aspectRatio (left to right), v: -1 to 1 (top to bottom)
            double u = (2.0 * ((x + Random::Double()) / (m_ViewportWidth - 1.0)) - 1.0) * m_ViewportAspectRatio * fovMul;
            double v = (2.0 * ((m_ViewportHeight - y + Random::Double()) / m_ViewportHeight) - 1.0) * fovMul;

            // Vec3 direction = Vec3(u, v, -m_FocalLength);
            // project direction from up = 0,1,0 and right = 1,0,0 to m_LocalUp and m_Right
            Vec3 projectedU = u * m_Right;
            Vec3 projectedV = v * m_LocalUp;
            Vec3 projectedF = -m_FocalLength * m_ViewDir;
            Vec3 projection = projectedU + projectedV + projectedF;

            return Ray(m_Origin, projection);
        }

    private:
        const Vec3 m_Up = Vec3(0.0, 1.0, 0.0);
        Vec3 m_Origin = Vec3(0.0, 0.0, 1.0);
        Vec3 m_ViewDir = Vec3(0.0, 0.0, -1.0);
        Vec3 m_LocalUp = Vec3(0.0, 1.0, 0.0);
        Vec3 m_Right = Vec3(1.0, 0.0, 0.0);
        double m_FOV = 90.0;
        double m_FocalLength = 1.0;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
        double m_ViewportAspectRatio = 0.0;
};
