#pragma once

#include "Math/Vec.h"
#include "Traceable.h"
#include "SceneComponent.h"

class TraceableComponent : public SceneComponent, Traceable {
public:
    TraceableComponent() : SceneComponent() {}
    TraceableComponent(Vec3 location, int materialIndex) : SceneComponent(location, materialIndex) {}

    virtual bool Trace(const Ray &ray, double traceDistMin, double traceDistMax, TraceResult& res) const override { return false; }
    virtual BoundingBox GetBoundingBox() const override { return BoundingBox(); }
};
