#include "Material/Material.h"

Material::Material()
    : m_Albedo(std::make_shared<Texture>(Vec3())),
      m_Emission(std::make_shared<Texture>(Vec3())),
      Roughness(1),
      Metallic(1.0),
      IndexOfRefraction(1.0),
      CanBounce(true) {}

Material::Material(Vec3 albedo,
                   double roughness, double metallic,
                   double indexOfRefraction, bool canBounce)
    : m_Albedo(std::make_shared<Texture>(albedo)),
      m_Emission(std::make_shared<Texture>(Vec3())),
      Roughness(roughness),
      Metallic(metallic),
      IndexOfRefraction(indexOfRefraction),
      CanBounce(canBounce) {}

Material::Material(Vec3 albedo,
                   Vec3 emmision,
                   double roughness, double metallic,
                   double indexOfRefraction, bool canBounce)
    : m_Albedo(std::make_shared<Texture>(albedo)),
      m_Emission(std::make_shared<Texture>(emmision)),
      Roughness(roughness),
      Metallic(metallic),
      IndexOfRefraction(indexOfRefraction),
      CanBounce(canBounce) {}

Material::Material(std::shared_ptr<Texture> albedo,
                  double roughness, double metallic,
                  double indexOfRefraction, bool canBounce)
    : m_Albedo(albedo),
      m_Emission(std::make_shared<Texture>(Vec3())),
      Roughness(roughness),
      Metallic(metallic),
      IndexOfRefraction(indexOfRefraction),
      CanBounce(canBounce) {}

Material::Material(std::shared_ptr<Texture> albedo,
                   std::shared_ptr<Texture> emission,
                   double roughness, double metallic,
                   double indexOfRefraction, bool canBounce)
    : m_Albedo(albedo),
      m_Emission(emission),
      Roughness(roughness),
      Metallic(metallic),
      IndexOfRefraction(indexOfRefraction),
      CanBounce(canBounce) {}

Vec3 Material::GetBounce(const Vec3& incoming, const Vec3& normal, bool isFrontFace) const {
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

Vec3 Material::refract(const Vec3& incoming, const Vec3& normal, double refractionRatio) {
    double cosTheta = std::fmin(Vec3::dot(-incoming, normal), 1.0);
    double sinTheta = std::sqrt(1.0 - (cosTheta * cosTheta));
    if (refractionRatio * sinTheta > 1.0 || reflectance(cosTheta, refractionRatio) > Random::Double()) {
        return Vec3::reflect(incoming, normal);
    }

    Vec3 outPerp =  refractionRatio * (incoming + (cosTheta * normal));
    Vec3 outPar = -std::sqrt(std::fabs(1.0 - Vec3::dot(outPerp, outPerp))) * normal;
    return outPerp + outPar;
}

double Material::reflectance(double cosine, double reflInd) {
    // Schlick's approximation for reflectance.
    double r0 = (1.0 - reflInd) / (1.0 + reflInd);
    r0 = r0 * r0;
    return r0 + ((1 - r0) * std::pow((1 - cosine), 5));
}
