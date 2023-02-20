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

        void SetFocalLength(double focalLength) { m_FocalLength = focalLength; }

        void SetFocusDist(double focusDist) { m_FocusDist = focusDist; }

        void SetAperture(double aperture) { m_Aperture = aperture; }

        void SetView(const Vec3& location, const Vec3& lookAt) {
            m_Origin = location;
            const Vec3& lookDir = location - lookAt;
            m_FocusDist = std::sqrt(Vec3::dot(lookDir, lookDir));
            m_ViewDir = Vec3::normalize(lookDir);
            m_Right = Vec3::normalize(Vec3::cross(m_Up, m_ViewDir));
            m_LocalUp = Vec3::cross(m_ViewDir, m_Right);
        }

        Ray GetRay(uint32_t x, uint32_t y) const {
            double theta = Utils::degreesToRadians(m_FOV);
            double fovMul = std::tan(theta / 2);
            // u: -1 to aspectRatio (left to right), v: -1 to 1 (top to bottom)
            double u = (2.0 * ((x + Random::Double()) / (m_ViewportWidth - 1.0)) - 1.0) * m_ViewportAspectRatio * fovMul * m_FocusDist;
            double v = (2.0 * ((m_ViewportHeight - y + Random::Double()) / m_ViewportHeight) - 1.0) * fovMul * m_FocusDist;

            // Vec3 direction = Vec3(u, v, -m_FocalLength);
            // project direction from up = 0,1,0 and right = 1,0,0 to m_LocalUp and m_Right
            Vec3 projectedU = u * m_Right;
            Vec3 projectedV = v * m_LocalUp;
            Vec3 projectedF = -m_FocalLength * m_FocusDist * m_ViewDir;
            Vec3 projection = projectedU + projectedV + projectedF;

            // Defocus Blur
            Vec2 rd = (m_Aperture / 2.0) * Vec2::random();
            Vec3 offset = (m_LocalUp * rd.X) + (m_Right * rd.Y);

            return Ray(m_Origin + offset, projection - offset);
        }

    private:
        const Vec3 m_Up = Vec3(0.0, 1.0, 0.0);
        Vec3 m_Origin = Vec3(0.0, 0.0, 1.0);
        Vec3 m_ViewDir = Vec3(0.0, 0.0, -1.0);
        Vec3 m_LocalUp = Vec3(0.0, 1.0, 0.0);
        Vec3 m_Right = Vec3(1.0, 0.0, 0.0);
        double m_FOV = 90.0;
        double m_FocalLength = 1.0;
        double m_FocusDist = 0.0;
        double m_Aperture = 0.0;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
        double m_ViewportAspectRatio = 0.0;
};
