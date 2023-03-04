#include "Scene/Sphere.h"

#include "Math/Utils.h"

bool Sphere::Trace(const Ray& ray, double distMin, double distMax, TraceResult& res) const {
    Vec3 camOffset = ray.Origin - m_WorldLocation;
    double a = Vec3::dot(ray.Direction , ray.Direction);
    double b = 2.0 * Vec3::dot(camOffset, ray.Direction);
    double c = Vec3::dot(camOffset, camOffset) - Radius * Radius;
    double discriminant = b * b - (4 * a * c);
    if (discriminant < 0.0) { return false; }

    double rearT = (-b + std::sqrt(discriminant)) / (2.0 * a);
    double nearT = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (nearT < distMin) { nearT = rearT; }
    if (nearT < distMin || nearT > distMax) { return false; }

    res.Success = true;
    res.HitDistance = nearT;
    res.WorldLocation = ray.At(nearT);
    res.SetFaceNormal(ray, (res.WorldLocation - m_WorldLocation) / Radius);
    res.ComponentUV = GetUV(res.WorldNormal);
    res.HitComponent = dynamic_cast<const TraceableComponent*>(this);
    return true;
}

BoundingBox Sphere::GetBoundingBox() const {
    return BoundingBox(m_WorldLocation - Vec3(Radius), m_WorldLocation + Vec3(Radius));
}

Vec2 Sphere::GetUV(const Vec3& point) {
    auto theta = acos(-point.Y);
    auto phi = atan2(-point.Z, point.X) + Utils::PI;

    return Vec2(phi / (2 * Utils::PI), theta / Utils::PI);
}
