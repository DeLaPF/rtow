#pragma once

#include "Math/Ray.h"

struct HitResult {
    bool DidHit = false;
    double HitDistance = 0.0;
    Vec3 WorldLocation = Vec3();
    Vec3 WorldNormal = Vec3();
    bool IsFrontFace = false;

    int HitIndex = -1;

    inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
        IsFrontFace = Vec3::dot(ray.Direction, outwardNormal) < 0;
        WorldNormal = IsFrontFace ? outwardNormal : -outwardNormal;
    }
};

class Renderable {
    public:
        virtual HitResult GetHitResult(const Ray& r, double hitDistMin, double hitDistMax) const = 0;
};
