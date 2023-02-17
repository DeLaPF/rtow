#pragma once

#include "Math/Ray.h"

struct HitResult {
    bool DidHit = false;
    double HitDistance = 0.0;
    Vec3 WorldLocation = Vec3();
    Vec3 WorldNormal = Vec3();
    bool IsFrontFace = false;

    inline void set_face_normal(const Ray& ray, const Vec3& outwardNormal) {
        IsFrontFace = Vec3Util::dot(ray.Direction, outwardNormal) < 0;
        WorldNormal = IsFrontFace ? outwardNormal : -outwardNormal;
    }
};

class SceneComponent {
    public:
        SceneComponent() : WorldLocation(Vec3()) {}
        SceneComponent(const Vec3& location) : WorldLocation(location) {}

        virtual Vec3& GetWorldLocation() { return WorldLocation; }
        virtual void SetWorldLocation(const Vec3& location) { WorldLocation = location; }

        virtual HitResult GetHitResult(const Ray& r, double hitDistMin, double hitDistMax) const = 0;
    protected:
        Vec3 WorldLocation;
};
