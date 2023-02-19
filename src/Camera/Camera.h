#pragma once

#include "Math/Ray.h"
#include "Math/Utils.h"
#include "Math/Vec3.h"
#include <cstdint>

class Camera {
    public:
        Camera() : Origin(Vec3(0, 0, 1)) {}
        Camera(Vec3 location) : Origin(location) {}

        void Resize(uint32_t width, uint32_t height) {
            if (width == m_ViewportWidth && height == m_ViewportHeight) {
                return;
            }

            m_ViewportWidth = width;
            m_ViewportHeight = height;
            m_ViewportAspectRatio = (double)width / height;
        }

        void Resize(uint32_t width, uint32_t height, double fov) {
            Resize(width, height);
            if (fov == m_FOV) {
                return;
            }

            m_FOV = fov;
        }

        Ray GetRay(uint32_t x, uint32_t y) const {
            double theta = Utils::degreesToRadians(m_FOV);
            double fovMul = std::tan(theta / 2);
            // u: -1 to aspectRatio (left to right), v: -1 to 1 (top to bottom)
            double u = (2.0 * ((x + Random::Double()) / (m_ViewportWidth - 1.0)) - 1.0) * m_ViewportAspectRatio * fovMul;
            double v = (2.0 * ((m_ViewportHeight - y + Random::Double()) / m_ViewportHeight) - 1.0) * fovMul;

            return Ray(Origin, Vec3(u, v, -m_FocalLength));
        }

    public:
        Vec3 Origin;
    private:
        double m_FOV = 90.0;
        double m_FocalLength = 1.0;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
        double m_ViewportAspectRatio = 0.0;
};
