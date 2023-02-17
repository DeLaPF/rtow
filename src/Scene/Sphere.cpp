#include "Sphere.h"

HitResult Sphere::GetHitResult(const Ray& ray, double distMin, double distMax) const {
    HitResult res;
    Vec3 camOffset = ray.Origin - WorldLocation;
    double a = Vec3Util::dot(ray.Direction , ray.Direction);
    double b = 2.0 * Vec3Util::dot(camOffset, ray.Direction);
    double c = Vec3Util::dot(camOffset, camOffset) - Radius * Radius;
    double discriminant = b * b - (4 * a * c);
    if (discriminant < 0.0) {
        return res;
    }

    double rearT = (-b + std::sqrt(discriminant)) / (2.0 * a);
    double nearT = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (nearT < distMin) {
        nearT = rearT;
    }

    if (nearT < distMin || nearT > distMax) {
        return res;
    }

    res.DidHit = true;
    res.HitDistance = nearT;
    res.WorldLocation = ray.At(nearT);
    res.WorldNormal = (res.WorldLocation - WorldLocation) / Radius;

    return res;
}
