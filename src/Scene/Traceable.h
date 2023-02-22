#pragma once

#include "BoundingVolume.h"
#include "Math/Ray.h"

struct TraceResult {
    bool Success = false;
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

class Traceable {
public:
    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const = 0;
    virtual BoundingBox GetBoundingBox() const = 0;
};