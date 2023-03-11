#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"
#include "Scene/TraceableComponent.h"

template <int TYPE>
class Rect : public TraceableComponent {
static_assert(TYPE >= 0 && TYPE <= 2, "Error: Rect<TYPE>, TYPE must be 0, 1, or 2");
public:
    Rect();
    Rect(Vec3 location, Vec2 dimensions, int materialIndex);
    Rect(Vec3 location, Vec2 dimensions, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;
    virtual BoundingBox GetBoundingBoxImpl() const override { return BoundingBox(MinBound, MaxBound); }
private:
    inline void Setup(Vec3 location, Vec2 dimensions, Vec3 rotation);
private:
    Vec3 MinBound;
    Vec3 MaxBound;
};

using RectXY = Rect<0>;
using RectXZ = Rect<1>;
using RectYZ = Rect<2>;
