#pragma once

#include <memory>
#include <vector>

#include "Scene/TraceableComponent.h"

class Box : public TraceableComponent {
public:
    Box() : TraceableComponent(), MinBound(Vec3(0, -1, -1)), MaxBound(Vec3(1, 0, 0)) {}
    Box(Vec3 minBound, Vec3 maxBound, int materialIndex);

    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBox() const override {
        return BoundingBox(Vec3(MinBound.X, MinBound.Y, MinBound.Z),
                           Vec3(MaxBound.X, MaxBound.Y, MaxBound.Z));
    }
public:
    Vec3 MinBound;
    Vec3 MaxBound;
    std::vector<std::shared_ptr<TraceableComponent>> Sides;
};
