#pragma once

#include <memory>
#include <vector>

#include "Scene/TraceableComponent.h"

class Box : public TraceableComponent {
public:
    Box();
    Box(Vec3 minBound, Vec3 maxBound, int materialIndex);
    Box(Vec3 minBound, Vec3 maxBound, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBoxImpl() const override {
        return BoundingBox(MinBound, MaxBound);
    }
public:
    Vec3 MinBound;
    Vec3 MaxBound;
    std::vector<std::shared_ptr<TraceableComponent>> Sides;
};
