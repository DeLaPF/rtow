#include "Scene/Sphere.h"

#include "Math/Utils.h"

Sphere::Sphere()
        : TraceableComponent(), Radius(0.5) {
    SetWorldLocation(Vec3());
    SetWorldRotation(Vec3());
}
Sphere::Sphere(Vec3 origin, double radius, int materialIndex)
        : TraceableComponent(origin, materialIndex), Radius(radius) {
    SetWorldLocation(origin);
    SetWorldRotation(Vec3());
}
Sphere::Sphere(Vec3 origin, double radius, Vec3 rotation, int materialIndex)
        : TraceableComponent(origin, rotation, materialIndex), Radius(radius) {
    SetWorldLocation(origin);
    SetWorldRotation(rotation);
}

bool Sphere::TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    double a = Vec3::dot(ray.Direction , ray.Direction);
    double b = 2.0 * Vec3::dot(ray.Origin, ray.Direction);
    double c = Vec3::dot(ray.Origin, ray.Origin) - Radius * Radius;
    double discriminant = b * b - (4 * a * c);
    if (discriminant < 0.0) { return false; }

    double rearT = (-b + std::sqrt(discriminant)) / (2.0 * a);
    double nearT = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (nearT < traceDistMin) { nearT = rearT; }
    if (nearT < traceDistMin || nearT > traceDistMax) { return false; }

    res.Success = true;
    res.HitDistance = nearT;
    res.WorldLocation = ray.At(nearT);
    res.SetFaceNormal(ray, res.WorldLocation / Radius);
    res.ComponentUV = GetUV(res.WorldNormal);
    return true;
}

BoundingBox Sphere::GetBoundingBoxImpl() const {
    return BoundingBox(-Vec3(Radius), Vec3(Radius));
}

Vec2 Sphere::GetUV(const Vec3& point) {
    auto theta = acos(-point.Y);
    auto phi = atan2(-point.Z, point.X) + Utils::PI;

    return Vec2(phi / (2 * Utils::PI), theta / Utils::PI);
}
