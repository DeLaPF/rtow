#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"
#include "Scene/TraceableComponent.h"

class RectXY : public TraceableComponent {
public:
    RectXY();
    RectXY(double minX, double maxX, double minY, double maxY, double z, int materialIndex);
    RectXY(double minX, double maxX, double minY, double maxY, double z, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBoxImpl() const override {
        return BoundingBox(MinBound, MaxBound);
    }
public:
    Vec3 MinBound;
    Vec3 MaxBound;
};

class RectXZ : public TraceableComponent {
public:
    RectXZ();
    RectXZ(double minX, double maxX, double minZ, double maxZ, double y, int materialIndex);
    RectXZ(double minX, double maxX, double minZ, double maxZ, double y, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBoxImpl() const override {
        return BoundingBox(MinBound, MaxBound);
    }
public:
    Vec3 MinBound;
    Vec3 MaxBound;
};

class RectYZ : public TraceableComponent {
public:
    RectYZ();
    RectYZ(double minY, double maxY, double minZ, double maxZ, double x, int materialIndex);
    RectYZ(double minY, double maxY, double minZ, double maxZ, double x, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBoxImpl() const override {
        return BoundingBox(MinBound, MaxBound);
    }
public:
    Vec3 MinBound;
    Vec3 MaxBound;
};
