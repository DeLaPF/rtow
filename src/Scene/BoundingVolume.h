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
        double invDX = 1.0f / ray.Direction.X;
        double t0X = (MinBound.X - ray.Origin.X) * invDX;
        double t1X = (MaxBound.X - ray.Origin.X) * invDX;
        if (invDX < 0.0f) { std::swap(t0X, t1X); }
        traceDistMin = t0X > traceDistMin ? t0X : traceDistMin;
        traceDistMax = t1X < traceDistMax ? t1X : traceDistMax;
        if (traceDistMax <= traceDistMin) { return false; }

        double invDY = 1.0f / ray.Direction.Y;
        double t0Y = (MinBound.Y - ray.Origin.Y) * invDY;
        double t1Y = (MaxBound.Y - ray.Origin.Y) * invDY;
        if (invDY < 0.0f) { std::swap(t0Y, t1Y); }
        traceDistMin = t0Y > traceDistMin ? t0Y : traceDistMin;
        traceDistMax = t1Y < traceDistMax ? t1Y : traceDistMax;
        if (traceDistMax <= traceDistMin) { return false; }

        double invDZ = 1.0f / ray.Direction.Z;
        double t0Z = (MinBound.Z - ray.Origin.Z) * invDZ;
        double t1Z = (MaxBound.Z - ray.Origin.Z) * invDZ;
        if (invDZ < 0.0f) { std::swap(t0Z, t1Z); }
        traceDistMin = t0Z > traceDistMin ? t0Z : traceDistMin;
        traceDistMax = t1Z < traceDistMax ? t1Z : traceDistMax;
        if (traceDistMax <= traceDistMin) { return false; }

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
