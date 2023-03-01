#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"

class Camera {
    public:
        Camera();

        void Resize(uint32_t width, uint32_t height);

        void SetFOV(double fov) { m_FOV = fov; }

        void SetFocalLength(double focalLength) { m_FocalLength = focalLength; }

        void SetFocusDist(double focusDist) { m_FocusDist = focusDist; }

        void SetAperture(double aperture) { m_Aperture = aperture; }

        void SetView(const Vec3& location, const Vec3& lookAt);

        Ray GetRay(uint32_t x, uint32_t y) const;
    private:
        const Vec3 m_Up;
        Vec3 m_Origin;
        Vec3 m_ViewDir;
        Vec3 m_LocalUp;
        Vec3 m_Right;
        double m_FOV;
        double m_FocalLength;
        double m_FocusDist;
        double m_Aperture;
        uint32_t m_ViewportWidth;
        uint32_t m_ViewportHeight;
        double m_ViewportAspectRatio;
};
