#include "Scene/AxisAlignedRect.h"

RectXY::RectXY()
        : TraceableComponent(),
          MinBound(Vec3(0, 0, -0.0001)),
          MaxBound(Vec3(1, 1, 0.0001)) {
    SetWorldLocation(Vec3());
    SetWorldRotation(Vec3());
}
RectXY::RectXY(Vec3 location, double xLen, double yLen, int materialIndex)
        : TraceableComponent(location, materialIndex),
          MinBound(Vec3(0, 0, -0.0001)),
          MaxBound(Vec3(xLen, yLen, location.Z + 0.0001)) {
    SetWorldLocation(location);
    SetWorldRotation(Vec3());
}
RectXY::RectXY(Vec3 location, double xLen, double yLen, Vec3 rotation, int materialIndex)
        : TraceableComponent(location, rotation, materialIndex),
          MinBound(Vec3(0, 0, -0.0001)),
          MaxBound(Vec3(xLen, yLen, location.Z + 0.0001)) {
    SetWorldLocation(location);
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
RectXZ::RectXZ(Vec3 location, double xLen, double zLen, int materialIndex)
        : TraceableComponent(location, materialIndex),
          MinBound(Vec3(0, -0.0001, 0)),
          MaxBound(Vec3(xLen, location.Y + 0.0001, zLen)) {
    SetWorldLocation(location);
    SetWorldRotation(Vec3());
}
RectXZ::RectXZ(Vec3 location, double xLen, double zLen, Vec3 rotation, int materialIndex)
        : TraceableComponent(location, rotation, materialIndex),
          MinBound(Vec3(0, -0.0001, 0)),
          MaxBound(Vec3(xLen, location.Y + 0.0001, zLen)) {
    SetWorldLocation(location);
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
RectYZ::RectYZ(Vec3 location, double yLen, double zLen, int materialIndex)
        : TraceableComponent(location, materialIndex),
          MinBound(Vec3(-0.0001, 0, 0)),
          MaxBound(Vec3(location.X + 0.0001, yLen, zLen)) {
    SetWorldLocation(location);
    SetWorldRotation(Vec3());
}
RectYZ::RectYZ(Vec3 location, double yLen, double zLen, Vec3 rotation, int materialIndex)
        : TraceableComponent(location, rotation, materialIndex),
          MinBound(Vec3(-0.0001, 0, 0)),
          MaxBound(Vec3(location.X + 0.0001, yLen, zLen)) {
    SetWorldLocation(location);
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
