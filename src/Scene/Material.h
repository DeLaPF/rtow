#pragma once

#include "Math/Vec3.h"

class Material {
    public:
        Material() : Albedo(Vec3()), Roughness(1.0) {}
        Material(const Vec3& albedo, double roughness) : Albedo(albedo), Roughness(roughness) {}

        virtual Vec3 GetBounce(const Vec3& incoming, const Vec3& normal) const {
            return ((1 - Roughness) * Vec3Util::reflect(incoming, normal)) + (Roughness * Vec3Util::randomBounce(normal));
        }
    
    public:
        Vec3 Albedo;
        double Roughness;
};
