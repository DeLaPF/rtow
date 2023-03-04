#pragma once

#include <memory>

#include "Math/Vec.h"
#include "Scene/Texture.h"

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

    virtual Vec3 GetBounce(const Vec3& incoming, const Vec3& normal, bool isFrontFace) const;

    virtual Vec3 Albedo(const Vec2& UV, const Vec3& point) { return m_Albedo->Value(UV, point); }

    virtual Vec3 Albedo() { return Albedo(Vec2(), Vec3()); }
public:
    double Roughness;
    double Metallic;
    double IndexOfRefraction;
private:
    std::shared_ptr<Texture> m_Albedo;
private:
    static Vec3 refract(const Vec3& incoming, const Vec3& normal, double refractionRatio);

    static double reflectance(double cosine, double reflInd);
};
