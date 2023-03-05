#include "Scene/AxisAlignedRect.h"

bool RectXY::Trace(const Ray &ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    double t = (m_WorldLocation.Z - ray.Origin.Z) / ray.Direction.Z;
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

bool RectXZ::Trace(const Ray &ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    double t = (m_WorldLocation.Y - ray.Origin.Y) / ray.Direction.Y;
    if (t < traceDistMin || t > traceDistMax) { return false; }

    Vec3 planeIntersection = ray.At(t);
    if (planeIntersection.X < MinBound.X || planeIntersection.X > MaxBound.X) { return false; }
    if (planeIntersection.Z < MinBound.Z || planeIntersection.Z > MaxBound.Z) { return false; }

    res.Success = true;
    res.HitDistance = t;
    res.WorldLocation = planeIntersection;
    res.SetFaceNormal(ray, Vec3(0, 1, 0));
    res.ComponentUV = Vec2((planeIntersection.Z - MinBound.Z) / (MaxBound.Z - MinBound.Z),
                           (planeIntersection.X - MinBound.X) / (MaxBound.X - MinBound.X));
    return true;
}

bool RectYZ::Trace(const Ray &ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    double t = (m_WorldLocation.X - ray.Origin.X) / ray.Direction.X;
    if (t < traceDistMin || t > traceDistMax) { return false; }

    Vec3 planeIntersection = ray.At(t);
    if (planeIntersection.Y < MinBound.Y || planeIntersection.Y > MaxBound.Y) { return false; }
    if (planeIntersection.Z < MinBound.Z || planeIntersection.Z > MaxBound.Z) { return false; }

    res.Success = true;
    res.HitDistance = t;
    res.WorldLocation = planeIntersection;
    res.SetFaceNormal(ray, Vec3(1, 0, 0));
    res.ComponentUV = Vec2((planeIntersection.Y - MinBound.Y) / (MaxBound.Y - MinBound.Y),
                           (planeIntersection.Z - MinBound.Z) / (MaxBound.Z - MinBound.Z));
    return true;
}
