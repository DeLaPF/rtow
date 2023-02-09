#pragma once

#include "Math/Ray.h"

struct HitResult {
    bool DidHit = false;
    double HitDistance = 0.0;
    Vec3 WorldLocation = Vec3();
    Vec3 WorldNormal = Vec3();
    bool IsFrontFace = false;

    inline void set_face_normal(const Ray& ray, const Vec3& outwardNormal) {
        IsFrontFace = dot(ray.Direction, outwardNormal) < 0;
        WorldNormal = IsFrontFace ? outwardNormal : -outwardNormal;
    }
};

class SceneComponent {
    public:
        virtual HitResult Hit(const Ray& r, double hitDistMin, double hitDistMax) const = 0;
};
