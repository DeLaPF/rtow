#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"
#include "Scene/Traceable.h"
#include "Scene/TraceableComponent.h"

class RectXY : public TraceableComponent {
public:
    RectXY()
        : TraceableComponent(),
          MinBound(Vec3(0, -1, -0.0001)),
          MaxBound(Vec3(1, 0, 0.0001)) {}

    RectXY(double minX, double maxX, double minY, double maxY, double z, int materialIndex)
        : TraceableComponent(Vec3(minX, maxY, z), materialIndex),
          MinBound(Vec3(minX, minY, z - 0.0001)),
          MaxBound(Vec3(maxX, maxY, z + 0.0001)) {}

    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBox() const override {
        return BoundingBox(Vec3(MinBound.X, MinBound.Y, MinBound.Z),
                           Vec3(MaxBound.X, MaxBound.Y, MaxBound.Z));
    }
public:
    Vec3 MinBound;
    Vec3 MaxBound;
};

class RectXZ : public TraceableComponent {
public:
    RectXZ()
        : TraceableComponent(),
          MinBound(Vec3(0, -0.0001, 0)),
          MaxBound(Vec3(1, 0.0001, 1)) {}

    RectXZ(double minX, double maxX, double minZ, double maxZ, double y, int materialIndex)
        : TraceableComponent(Vec3(minX, y, minZ), materialIndex),
          MinBound(Vec3(minX, y - 0.0001, minZ)),
          MaxBound(Vec3(maxX, y + 0.0001, maxZ)) {}

    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBox() const override {
        return BoundingBox(Vec3(MinBound.X, MinBound.Y, MinBound.Z),
                           Vec3(MaxBound.X, MaxBound.Y, MaxBound.Z));
    }
public:
    Vec3 MinBound;
    Vec3 MaxBound;
};

class RectYZ : public TraceableComponent {
public:
    RectYZ()
        : TraceableComponent(),
          MinBound(Vec3(-0.0001, -1, -1)),
          MaxBound(Vec3(0.0001, 0, 0)) {}

    RectYZ(double minY, double maxY, double minZ, double maxZ, double x, int materialIndex)
        : TraceableComponent(Vec3(x, maxY, maxZ), materialIndex),
          MinBound(Vec3(x - 0.0001, minY, minZ)),
          MaxBound(Vec3(x + 0.0001, maxY, maxZ)) {}

    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBox() const override {
        return BoundingBox(Vec3(MinBound.X, MinBound.Y, MinBound.Z),
                           Vec3(MaxBound.X, MaxBound.Y, MaxBound.Z));
    }
public:
    Vec3 MinBound;
    Vec3 MaxBound;
};
