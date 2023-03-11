#include "Scene/TraceableComponent.h"

#include <limits>

TraceableComponent::TraceableComponent()
        : SceneComponent() {
    SetWorldRotation(Vec3());
}
TraceableComponent::TraceableComponent(Vec3 location, int materialIndex)
        : SceneComponent(location, materialIndex) {
    SetWorldRotation(Vec3());
}
TraceableComponent::TraceableComponent(Vec3 location, Vec3 rotation, int materialIndex)
        : SceneComponent(location, rotation, materialIndex) {
    SetWorldRotation(rotation);
}

void TraceableComponent::SetWorldRotation(Vec3 rotation) {
    SceneComponent::SetWorldRotation(rotation);

    BoundingBox bounding = GetBoundingBoxImpl();
    BoundingBox::BoundRotated(bounding, m_SinPsi, m_CosPsi, 0);
    BoundingBox::BoundRotated(bounding, m_SinTheta, m_CosTheta, 1);
    BoundingBox::BoundRotated(bounding, m_SinPhi, m_CosPhi, 2);
    m_RotatedBoundingBox = bounding;
}

bool TraceableComponent::Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    if (!GetBoundingBox().DoesOverlap(ray, traceDistMin, traceDistMax)) { return false; }

    Ray translated = Ray(ray.Origin - m_WorldLocation, ray.Direction);
    Vec3 originInvRot = translated.Origin;
    Vec3::Rotate(originInvRot, -m_SinPhi, m_CosPhi, 2);
    Vec3::Rotate(originInvRot, -m_SinTheta, m_CosTheta, 1);
    Vec3::Rotate(originInvRot, -m_SinPsi, m_CosPsi, 0);
    Vec3 directionInvRot = translated.Direction;
    Vec3::Rotate(directionInvRot, -m_SinPhi, m_CosPhi, 2);
    Vec3::Rotate(directionInvRot, -m_SinTheta, m_CosTheta, 1);
    Vec3::Rotate(directionInvRot, -m_SinPsi, m_CosPsi, 0);

    Ray rotated = Ray(originInvRot, directionInvRot);
    if (!TraceImpl(rotated, traceDistMin, traceDistMax, res)) { return false; }

    Vec3 worldLocationRot = res.WorldLocation;
    Vec3::Rotate(worldLocationRot, m_SinPsi, m_CosPsi, 0);
    Vec3::Rotate(worldLocationRot, m_SinTheta, m_CosTheta, 1);
    Vec3::Rotate(worldLocationRot, m_SinPhi, m_CosPhi, 2);
    Vec3 worldNormalRot = res.WorldNormal;
    Vec3::Rotate(worldNormalRot, m_SinPsi, m_CosPsi, 0);
    Vec3::Rotate(worldNormalRot, m_SinTheta, m_CosTheta, 1);
    Vec3::Rotate(worldNormalRot, m_SinPhi, m_CosPhi, 2);

    res.WorldLocation = worldLocationRot + m_WorldLocation;
    if (Vec3::dot(res.WorldNormal, worldNormalRot) < 0) {
        res.SetFaceNormal(rotated, worldNormalRot);
        res.SetFaceNormal(translated, res.WorldNormal);
    } else {
        res.WorldNormal = worldNormalRot;
    }
    return true;
}

BoundingBox TraceableComponent::GetBoundingBox() const {
    return BoundingBox(m_RotatedBoundingBox.MinBound + m_WorldLocation,
                       m_RotatedBoundingBox.MaxBound + m_WorldLocation);
}
