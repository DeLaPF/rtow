#pragma once

#include "Texture.h"
#include "Math/Vec.h"

#include <memory>

class Material {
    public:
        Material()
            : m_Albedo(std::make_shared<Texture>(Vec3())), Roughness(1), Metallic(1.0), IndexOfRefraction(1.0) {}

        Material(Vec3 albedo)
            : m_Albedo(std::make_shared<Texture>(albedo)), Roughness(1), Metallic(1.0), IndexOfRefraction(1.0) {}
        Material(Vec3 albedo, double roughness)
            : m_Albedo(std::make_shared<Texture>(albedo)), Roughness(roughness), Metallic(1.0), IndexOfRefraction(1.0) {}
        Material(Vec3 albedo, double roughness, double metallic, double indexOfRefraction)
            : m_Albedo(std::make_shared<Texture>(albedo)), Roughness(roughness), Metallic(metallic), IndexOfRefraction(indexOfRefraction) {}

        Material(std::shared_ptr<Texture> texture)
            : m_Albedo(texture), Roughness(1), Metallic(1.0), IndexOfRefraction(1.0) {}
        Material(std::shared_ptr<Texture> texture, double roughness)
            : m_Albedo(texture), Roughness(roughness), Metallic(1.0), IndexOfRefraction(1.0) {}
        Material(std::shared_ptr<Texture> texture, double roughness, double metallic, double indexOfRefraction)
            : m_Albedo(texture), Roughness(roughness), Metallic(metallic), IndexOfRefraction(indexOfRefraction) {}

        virtual Vec3 GetBounce(const Vec3& incoming, const Vec3& normal, bool isFrontFace) const {
            Vec3 nonDielectricComp = Vec3();
            if (Metallic != 0.0) {
                Vec3 diffuseComp =  Roughness != 0 ? Vec3::randomBounce(normal) : Vec3();
                Vec3 metalComp = Roughness != 1 ? Vec3::reflect(incoming, normal) : Vec3();
                nonDielectricComp = (Roughness * diffuseComp) + ((1 - Roughness) * metalComp);
            }

            Vec3 dielectricComp = Vec3();
            if (Metallic != 1.0) {
                double refractionRatio = isFrontFace ? (1.0 / IndexOfRefraction) : IndexOfRefraction;
                dielectricComp = refract(Vec3::normalize(incoming), normal, refractionRatio);
            }

            return (Metallic * nonDielectricComp) + ((1 - Metallic) * dielectricComp);
        }

        virtual Vec3 Albedo(const Vec2& UV, const Vec3& point) { return m_Albedo->Value(UV, point); }

        virtual Vec3 Albedo() { return Albedo(Vec2(), Vec3()); }
    public:
        double Roughness;
        double Metallic;
        double IndexOfRefraction;
    private:
        std::shared_ptr<Texture> m_Albedo;
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
