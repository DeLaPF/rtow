#pragma once

#include "Math/Vec.h"
#include "Scene/BoundingVolume.h"
#include "Scene/TraceableComponent.h"

class Sphere : public TraceableComponent {
public:
    Sphere() : TraceableComponent(), Radius(0.5) {}
    Sphere(Vec3 origin, double radius, int materialIndex)
        : TraceableComponent(origin, materialIndex), Radius(radius) {}
    Sphere(Vec3 origin, double radius, Vec3 rotation, int materialIndex)
        : TraceableComponent(origin, rotation, materialIndex), Radius(radius) {}

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBoxImpl() const override;

    static Vec2 GetUV(const Vec3& point);
public:
    double Radius;
};
