#include "Scene/AxisAlignedRect.h"

RectXY::RectXY()
        : TraceableComponent(),
          MinBound(Vec3(0, 0, -0.0001)),
          MaxBound(Vec3(1, 1, 0.0001)) {
    SetWorldLocation(Vec3());
    SetWorldRotation(Vec3());
}
RectXY::RectXY(double minX, double maxX, double minY, double maxY, double z, int materialIndex)
        : TraceableComponent(Vec3(minX, minY, z), materialIndex),
          MinBound(Vec3(0, 0, -0.0001)),
          MaxBound(Vec3(maxX - minX, maxY - minY, 0.0001)) {
    SetWorldLocation(Vec3(minX, minY, z));
    SetWorldRotation(Vec3());
}
RectXY::RectXY(double minX, double maxX, double minY, double maxY, double z, Vec3 rotation, int materialIndex)
        : TraceableComponent(Vec3(minX, minY, z), rotation, materialIndex),
          MinBound(Vec3(0, 0, -0.0001)),
          MaxBound(Vec3(maxX - minX, maxY - minY, 0.0001)) {
    SetWorldLocation(Vec3(minX, minY, z));
    SetWorldRotation(rotation);
}

bool RectXY::TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    double t = -ray.Origin.Z / ray.Direction.Z;
    if (t < traceDistMin || t > traceDistMax) { return false; }

    Vec3 planeIntersection = ray.At(t);
    if (planeIntersection.X < MinBound.X || planeIntersection.X > MaxBound.X) { return false; }
    if (planeIntersection.Y < MinBound.Y || planeIntersection.Y > MaxBound.Y) { return false; }

    res.Success = true;
    res.HitDistance = t;
    res.WorldLocation = planeIntersection;
    res.SetFaceNormal(ray, Vec3(0, 0, 1));
    res.ComponentUV = Vec2((planeIntersection.X - MinBound.X) / (MaxBound.X - MinBound.X),
                           (planeIntersection.Y - MinBound.Y) / (MaxBound.Y - MinBound.Y));
    return true;
}

RectXZ::RectXZ()
        : TraceableComponent(),
          MinBound(Vec3(0, -0.0001, 0)),
          MaxBound(Vec3(1, 0.0001, 1)) {
    SetWorldLocation(Vec3());
    SetWorldRotation(Vec3());
}
RectXZ::RectXZ(double minX, double maxX, double minZ, double maxZ, double y, int materialIndex)
        : TraceableComponent(Vec3(minX, y, minZ), materialIndex),
          MinBound(Vec3(0, -0.0001, 0)),
          MaxBound(Vec3(maxX - minX, 0.0001, maxZ - minZ)) {
    SetWorldLocation(Vec3(minX, y, minZ));
    SetWorldRotation(Vec3());
}
RectXZ::RectXZ(double minX, double maxX, double minZ, double maxZ, double y, Vec3 rotation, int materialIndex)
        : TraceableComponent(Vec3(minX, y, minZ), rotation, materialIndex),
          MinBound(Vec3(0, -0.0001, 0)),
          MaxBound(Vec3(maxX - minX, 0.0001, maxZ - minZ)) {
    SetWorldLocation(Vec3(minX, y, minZ));
    SetWorldRotation(rotation);
}

bool RectXZ::TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    double t = -ray.Origin.Y / ray.Direction.Y;
    if (t < traceDistMin || t > traceDistMax) { return false; }

    Vec3 planeIntersection = ray.At(t);
    if (planeIntersection.X < MinBound.X || planeIntersection.X > MaxBound.X) { return false; }
    if (planeIntersection.Z < MinBound.Z || planeIntersection.Z > MaxBound.Z) { return false; }

    res.Success = true;
    res.HitDistance = t;
    res.WorldLocation = planeIntersection;
    res.SetFaceNormal(ray, Vec3(0, 1, 0));
    res.ComponentUV = Vec2((planeIntersection.X - MinBound.X) / (MaxBound.X - MinBound.X),
                           (planeIntersection.Z - MinBound.Z) / (MaxBound.Z - MinBound.Z));
    return true;
}

RectYZ::RectYZ()
        : TraceableComponent(),
          MinBound(Vec3(-0.0001, 0, 0)),
          MaxBound(Vec3(0.0001, 1, 1)) {
    SetWorldLocation(Vec3());
    SetWorldRotation(Vec3());
}
RectYZ::RectYZ(double minY, double maxY, double minZ, double maxZ, double x, int materialIndex)
    : TraceableComponent(Vec3(x, minY, minZ), materialIndex),
      MinBound(Vec3(-0.0001, 0, 0)),
      MaxBound(Vec3(0.0001, maxY - minY, maxZ - minZ)) {
    SetWorldLocation(Vec3(x, minY, minZ));
    SetWorldRotation(Vec3());
}
RectYZ::RectYZ(double minY, double maxY, double minZ, double maxZ, double x, Vec3 rotation, int materialIndex)
    : TraceableComponent(Vec3(x, minY, minZ), rotation, materialIndex),
      MinBound(Vec3(-0.0001, 0, 0)),
      MaxBound(Vec3(0.0001, maxY - minY, maxZ - minZ)) {
    SetWorldLocation(Vec3(x, minY, minZ));
    SetWorldRotation(rotation);
}

bool RectYZ::TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    double t = -ray.Origin.X / ray.Direction.X;
    if (t < traceDistMin || t > traceDistMax) { return false; }

    Vec3 planeIntersection = ray.At(t);
    if (planeIntersection.Y < MinBound.Y || planeIntersection.Y > MaxBound.Y) { return false; }
    if (planeIntersection.Z < MinBound.Z || planeIntersection.Z > MaxBound.Z) { return false; }

    res.Success = true;
    res.HitDistance = t;
    res.WorldLocation = planeIntersection;
    res.SetFaceNormal(ray, Vec3(1, 0, 0));
    res.ComponentUV = Vec2((planeIntersection.Z - MinBound.Z) / (MaxBound.Z - MinBound.Z),
                           (planeIntersection.Y - MinBound.Y) / (MaxBound.Y - MinBound.Y));
    return true;
}
