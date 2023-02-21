#pragma once

#include "Math/Vec.h"

class Material {
    public:
        Material()
            : Albedo(Vec3()), Roughness(1), Metallic(1.0), IndexOfRefraction(1.0) {}
        Material(Vec3 albedo)
            : Albedo(albedo), Roughness(1), Metallic(1.0), IndexOfRefraction(1.0) {}
        Material(Vec3 albedo, double roughness)
            : Albedo(albedo), Roughness(roughness), Metallic(1.0), IndexOfRefraction(1.0) {}
        Material(Vec3 albedo, double roughness, double metallic, double indexOfRefraction)
            : Albedo(albedo), Roughness(roughness), Metallic(metallic), IndexOfRefraction(indexOfRefraction) {}

        virtual Vec3 GetBounce(const Vec3& incoming, const Vec3& normal, bool isFrontFace) const {
            if (Metallic == 1.0) {
                return ((1 - Roughness) * Vec3::reflect(incoming, normal)) +
                    (Roughness * Vec3::randomBounce(normal));
            }
            double refractionRatio = isFrontFace ? (1.0 / IndexOfRefraction) : IndexOfRefraction;
            return refract(Vec3::normalize(incoming), normal, refractionRatio);
        }
    
    public:
        Vec3 Albedo;
        double Roughness;
        double Metallic;
        double IndexOfRefraction;
    private:
        static Vec3 refract(const Vec3& incoming, const Vec3& normal, double refractionRatio) {
            double cosTheta = std::fmin(Vec3::dot(-incoming, normal), 1.0);
            double sinTheta = std::sqrt(1.0 - (cosTheta * cosTheta));
            if (refractionRatio * sinTheta > 1.0 || reflectance(cosTheta, refractionRatio) > Random::Double()) {
                return Vec3::reflect(incoming, normal);
            }

            Vec3 outPerp =  refractionRatio * (incoming + (cosTheta * normal));
            Vec3 outPar = -std::sqrt(std::fabs(1.0 - Vec3::dot(outPerp, outPerp))) * normal;
            return outPerp + outPar;
        }

        // Schlick's approximation for reflectance.
        static double reflectance(double cosine, double reflInd) {
            double r0 = (1.0 - reflInd) / (1.0 + reflInd);
            r0 = r0 * r0;
            return r0 + ((1 - r0) * std::pow((1 - cosine), 5));
        }
};
