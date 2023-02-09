#pragma once

#include "SceneComponent.h"
#include "Math/Vec3.h"

class Sphere : public SceneComponent {
    public:
        Sphere() : Origin(Vec3()), Radius(0.5) {}
        Sphere(Vec3 origin, double radius) : Origin(origin), Radius(radius) {};

        virtual HitResult Hit(const Ray& r, double distMin, double distMax) const override;

    public:
        Vec3 Origin;
        double Radius;
};
