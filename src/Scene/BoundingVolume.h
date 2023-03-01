#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"

class BoundingVolume {
public:
    virtual bool DoesOverlap(const Ray& ray, double traceDistMin, double traceDistMax) const = 0;
};

class BoundingBox : public BoundingVolume {
public:
    BoundingBox() : MinBound(Vec3(-1)), MaxBound(Vec3(1)) {}
    BoundingBox(Vec3 minBound, Vec3 maxBound)
        : MinBound(minBound), MaxBound(maxBound) {}

    virtual bool DoesOverlap(const Ray& ray, double traceDistMin, double traceDistMax) const override;

    static BoundingBox Surrounding(const BoundingBox& a, const BoundingBox& b);
public:
    Vec3 MinBound;
    Vec3 MaxBound;
};

class BoundingBoxComparator {
public:
    BoundingBoxComparator(uint32_t axis) : m_Axis(axis % 3) {}

    bool operator()(const BoundingBox& a, const BoundingBox& b) {
        return a.MinBound[m_Axis] < b.MinBound[m_Axis];
    }
private:
    uint32_t m_Axis;
};
