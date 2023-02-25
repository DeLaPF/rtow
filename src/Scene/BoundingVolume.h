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
        double t0X = std::fmin((MinBound.X - ray.Origin.X) / ray.Direction.X,
                              (MaxBound.X - ray.Origin.X) / ray.Direction.X);
        double t1X = std::fmax((MinBound.X - ray.Origin.X) / ray.Direction.X,
                              (MaxBound.X - ray.Origin.X) / ray.Direction.X);
        traceDistMin = std::fmax(t0X, traceDistMin);
        traceDistMax = std::fmin(t1X, traceDistMax);
        if (traceDistMin >= traceDistMax) { return false; }

        double t0Y = std::fmin((MinBound.Y - ray.Origin.Y) / ray.Direction.Y,
                              (MaxBound.Y - ray.Origin.Y) / ray.Direction.Y);
        double t1Y = std::fmax((MinBound.Y - ray.Origin.Y) / ray.Direction.Y,
                              (MaxBound.Y - ray.Origin.Y) / ray.Direction.Y);
        traceDistMin = std::fmax(t0Y, traceDistMin);
        traceDistMax = std::fmin(t1Y, traceDistMax);
        if (traceDistMin >= traceDistMax) { return false; }

        double t0Z = std::fmin((MinBound.Z - ray.Origin.Z) / ray.Direction.Z,
                              (MaxBound.Z - ray.Origin.Z) / ray.Direction.Z);
        double t1Z = std::fmax((MinBound.Z - ray.Origin.Z) / ray.Direction.Z,
                              (MaxBound.Z - ray.Origin.Z) / ray.Direction.Z);
        traceDistMin = std::fmax(t0Z, traceDistMin);
        traceDistMax = std::fmin(t1Z, traceDistMax);
        if (traceDistMin >= traceDistMax) { return false; }

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
