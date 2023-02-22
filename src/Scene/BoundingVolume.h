#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"
#include <cmath>

class BoundingVolume {
public:
    virtual bool DoesOverlap(const Ray& ray, double traceDistMin, double traceDistMax) const { return false; }
};

class BoundingBox : public BoundingVolume {
public:
    BoundingBox() : MinBound(Vec3(-1)), MaxBound(Vec3(1)) {}
    BoundingBox(Vec3 minBound, Vec3 maxBound) : MinBound(minBound), MaxBound(maxBound) {}

    virtual bool DoesOverlap(const Ray& ray, double traceDistMin, double traceDistMax) const override {
        for (int i = 0; i < 3; i++) {
            double t0 = (MinBound[i] - ray.Origin[i]) / ray.Direction[i];
            double t1 = (MaxBound[i] - ray.Origin[i]) / ray.Direction[i];
            if (t0 > t1) { std::swap(t0, t1); }
            traceDistMin = std::fmax(t0, traceDistMin);
            traceDistMax = std::fmin(t1, traceDistMax);
            if (traceDistMin >= traceDistMax) { return false; }
        }
        return true;
    }

    static BoundingBox Surrounding(const BoundingBox& a, const BoundingBox& b) {
        Vec3 min = Vec3(std::fmin(a.MinBound.X, b.MinBound.X),
                        std::fmin(a.MinBound.Y, b.MinBound.Y),
                        std::fmin(a.MinBound.Z, b.MinBound.Z));
        Vec3 max = Vec3(std::fmax(a.MaxBound.X, b.MaxBound.X),
                        std::fmax(a.MaxBound.Y, b.MaxBound.Y),
                        std::fmax(a.MaxBound.Z, b.MaxBound.Z));
        return BoundingBox(min, max);
    }
public:
    Vec3 MinBound, MaxBound;
};
