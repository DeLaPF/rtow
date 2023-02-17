#pragma once

#include "Math/Ray.h"

struct HitResult {
    bool DidHit = false;
    double HitDistance = 0.0;
    Vec3 WorldLocation = Vec3();
    Vec3 WorldNormal = Vec3();
    bool IsFrontFace = false;

    int HitIndex = -1;

    inline void set_face_normal(const Ray& ray, const Vec3& outwardNormal) {
        IsFrontFace = Vec3Util::dot(ray.Direction, outwardNormal) < 0;
        WorldNormal = IsFrontFace ? outwardNormal : -outwardNormal;
    }
};

class SceneComponent {
    public:
        SceneComponent() : m_WorldLocation(Vec3()) {}
        SceneComponent(const Vec3& location, int materialIndex)
            : m_WorldLocation(location), m_MaterialIndex(materialIndex) {}

        virtual Vec3& GetWorldLocation() { return m_WorldLocation; }
        virtual void SetWorldLocation(const Vec3& location) { m_WorldLocation = location; }

        virtual int GetMaterialIndex() { return m_MaterialIndex; }
        virtual void SetMaterialIndex(int index) { m_MaterialIndex = index; }

        virtual HitResult GetHitResult(const Ray& r, double hitDistMin, double hitDistMax) const {
            HitResult defaultRes;
            return defaultRes;
        }
    protected:
        Vec3 m_WorldLocation;
        int m_MaterialIndex = 0;
};
