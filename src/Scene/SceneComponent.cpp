#include "Scene/SceneComponent.h"

#include <cmath>

#include "Math/Utils.h"

SceneComponent::SceneComponent()
        : m_MaterialIndex(0) {
    SetWorldLocation(Vec3());
    SetWorldRotation(Vec3());
}
SceneComponent::SceneComponent(Vec3 location, int materialIndex)
        : m_MaterialIndex(materialIndex) {
    SetWorldLocation(location);
    SetWorldRotation(Vec3());
}
SceneComponent::SceneComponent(Vec3 location, Vec3 rotation, int materialIndex)
        : m_MaterialIndex(materialIndex) {
    SetWorldLocation(location);
    SetWorldRotation(rotation);
}

void SceneComponent::SetWorldRotation(Vec3 rotation) {
    double phi = Utils::degreesToRadians(rotation.X);
    double theta = Utils::degreesToRadians(rotation.Y);
    double psi = Utils::degreesToRadians(rotation.Z);
    m_SinPhi = std::sin(phi);
    m_CosPhi = std::cos(phi);
    m_SinTheta = std::sin(theta);
    m_CosTheta = std::cos(theta);
    m_SinPsi = std::sin(psi);
    m_CosPsi = std::cos(psi);
    m_WorldRotation = rotation;
}
