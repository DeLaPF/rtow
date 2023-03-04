#include "Scene/Material.h"

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
