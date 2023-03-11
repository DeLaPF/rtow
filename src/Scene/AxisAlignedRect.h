#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"
#include "Scene/TraceableComponent.h"

class RectXY : public TraceableComponent {
public:
    RectXY();
    RectXY(Vec3 location, double xLen, double yLen, int materialIndex);
    RectXY(Vec3 location, double xLen, double yLen, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;
    virtual BoundingBox GetBoundingBoxImpl() const override { return BoundingBox(MinBound, MaxBound); }
private:
    Vec3 MinBound;
    Vec3 MaxBound;
};

class RectXZ : public TraceableComponent {
public:
    RectXZ();
    RectXZ(Vec3 location, double xLen, double zLen, int materialIndex);
    RectXZ(Vec3 location, double xLen, double zLen, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;
    virtual BoundingBox GetBoundingBoxImpl() const override { return BoundingBox(MinBound, MaxBound); }
private:
    Vec3 MinBound;
    Vec3 MaxBound;
};

class RectYZ : public TraceableComponent {
public:
    RectYZ();
    RectYZ(Vec3 location, double yLen, double zLen, int materialIndex);
    RectYZ(Vec3 location, double yLen, double zLen, Vec3 rotation, int materialIndex);

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;
    virtual BoundingBox GetBoundingBoxImpl() const override { return BoundingBox(MinBound, MaxBound); }
private:
    Vec3 MinBound;
    Vec3 MaxBound;
};
