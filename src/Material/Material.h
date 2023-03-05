#pragma once

#include <memory>

#include "Math/Vec.h"
#include "Material/Texture.h"

class Material {
public:
    Material();
    Material(Vec3 albedo, double roughness = 1.0, double metallic = 1.0, double indexOfRefraction = 1.0, bool canBounce = true);
    Material(Vec3 albedo, Vec3 emission, double roughness = 1.0, double metallic = 1.0, double indexOfRefraction = 1.0, bool canBounce = true);
    Material(std::shared_ptr<Texture> albedo, double roughness = 1.0, double metallic = 1.0, double indexOfRefraction = 1.0, bool canBounce = true);
    Material(std::shared_ptr<Texture> albedo, std::shared_ptr<Texture> emission, double roughness = 1.0, double metallic = 1.0, double indexOfRefraction = 1.0, bool canBounce = true);

    virtual Vec3 GetBounce(const Vec3& incoming, const Vec3& normal, bool isFrontFace) const;

    virtual Vec3 Albedo(const Vec2& UV, const Vec3& point) { return m_Albedo->Value(UV, point); }
    virtual Vec3 Albedo() { return Albedo(Vec2(), Vec3()); }

    virtual Vec3 Emission(const Vec2& UV, const Vec3& point) { return m_Emission->Value(UV, point); }
    virtual Vec3 Emission() { return Emission(Vec2(), Vec3()); }
public:
    double Roughness;
    double Metallic;
    double IndexOfRefraction;
    bool CanBounce;
private:
    std::shared_ptr<Texture> m_Albedo;
    std::shared_ptr<Texture> m_Emission;
private:
    static Vec3 refract(const Vec3& incoming, const Vec3& normal, double refractionRatio);

    static double reflectance(double cosine, double reflInd);
};
