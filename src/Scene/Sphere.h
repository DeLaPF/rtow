#pragma once

#include "Scene/BoundingVolume.h"
#include "TraceableComponent.h"
#include "Math/Utils.h"
#include "Math/Vec.h"

class Sphere : public TraceableComponent {
public:
    Sphere() : TraceableComponent(), Radius(0.5) {}
    Sphere(Vec3 origin, double radius, int materialIndex)
        : TraceableComponent(origin, materialIndex), Radius(radius) {}

    bool Trace(const Ray& ray, double distMin, double distMax, TraceResult& res) const override {
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
        return true;
    }

    BoundingBox GetBoundingBox() const override {
        return BoundingBox(m_WorldLocation - Vec3(Radius), m_WorldLocation + Vec3(Radius));
    }
public:
    double Radius;
public:
    static Vec2 GetUV(const Vec3& point) {
        auto theta = acos(-point.Y);
        auto phi = atan2(-point.Z, point.X) + Utils::PI;

        return Vec2(phi / (2 * Utils::PI), theta / Utils::PI);
    }
};
