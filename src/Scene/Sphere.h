#pragma once

#include "SceneComponent.h"
#include "Math/Vec3.h"

class Sphere : public SceneComponent {
    public:
        Sphere() : SceneComponent(), Radius(0.5) {}
        Sphere(const Vec3& origin, double radius, int materialIndex)
            : SceneComponent(origin, materialIndex), Radius(radius) {}

        virtual HitResult GetHitResult(const Ray& r, double distMin, double distMax) const override;
    public:
        double Radius;
};
