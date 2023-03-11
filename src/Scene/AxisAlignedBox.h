#pragma once

#include <memory>
#include <vector>

#include "Scene/TraceableComponent.h"

class Box : public TraceableComponent {
public:
    Box();
    Box(Vec3 location, Vec3 dimensions, int materialIndex);
    Box(Vec3 location, Vec3 dimensions, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;
    virtual BoundingBox GetBoundingBoxImpl() const override { return BoundingBox(MinBound, MaxBound); }
private:
    Vec3 MinBound;
    Vec3 MaxBound;
    std::vector<std::shared_ptr<TraceableComponent>> Sides;
};
