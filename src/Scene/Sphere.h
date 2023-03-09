#pragma once

#include "Math/Vec.h"
#include "Scene/BoundingVolume.h"
#include "Scene/TraceableComponent.h"

class Sphere : public TraceableComponent {
public:
    Sphere();
    Sphere(Vec3 origin, double radius, int materialIndex);
    Sphere(Vec3 origin, double radius, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBoxImpl() const override;

    static Vec2 GetUV(const Vec3& point);
public:
    double Radius;
};
