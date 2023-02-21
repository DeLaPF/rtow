#pragma once

#include "RenderableComponent.h"
#include "Math/Vec3.h"

class Sphere : public RenderableComponent {
    public:
        Sphere() : RenderableComponent(), Radius(0.5) {}
        Sphere(Vec3 origin, double radius, int materialIndex)
            : RenderableComponent(origin, materialIndex), Radius(radius) {}

        virtual HitResult GetHitResult(const Ray& r, double distMin, double distMax) const override;
    public:
        double Radius;
};
