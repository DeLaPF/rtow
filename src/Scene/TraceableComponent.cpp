#include "Scene/TraceableComponent.h"
#include "Scene/BoundingVolume.h"

#include <limits>

void TraceableComponent::SetWorldRotation(Vec3 rotation) {
    SceneComponent::SetWorldRotation(rotation);

    BoundingBox bounding = GetBoundingBoxImpl();
    BoundingBox::Rotate(bounding, m_SinPsi, m_CosPsi, 0);
    BoundingBox::Rotate(bounding, m_SinTheta, m_CosTheta, 1);
    BoundingBox::Rotate(bounding, m_SinPhi, m_CosPhi, 2);
    m_RotatedBoundingBox = bounding;
}

bool TraceableComponent::Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    Vec3 originInvRot = ray.Origin - m_WorldLocation;
    Vec3::Rotate(originInvRot, -m_SinPhi, m_CosPhi, 2);
    Vec3::Rotate(originInvRot, -m_SinTheta, m_CosTheta, 1);
    Vec3::Rotate(originInvRot, -m_SinPsi, m_CosPsi, 0);
    Vec3 directionInvRot = ray.Direction;
    Vec3::Rotate(directionInvRot, -m_SinPhi, m_CosPhi, 2);
    Vec3::Rotate(directionInvRot, -m_SinTheta, m_CosTheta, 1);
    Vec3::Rotate(directionInvRot, -m_SinPsi, m_CosPsi, 0);

    Ray translated = Ray(ray.Origin - m_WorldLocation, ray.Direction);
    Ray transformed = Ray(originInvRot, directionInvRot);
    if (!TraceImpl(transformed, traceDistMin, traceDistMax, res)) { return false; }

    Vec3 worldLocationRot = res.WorldLocation;
    Vec3::Rotate(worldLocationRot, m_SinPsi, m_CosPsi, 0);
    Vec3::Rotate(worldLocationRot, m_SinTheta, m_CosTheta, 1);
    Vec3::Rotate(worldLocationRot, m_SinPhi, m_CosPhi, 2);
    Vec3 worldNormalRot = res.WorldNormal;
    Vec3::Rotate(worldNormalRot, m_SinPsi, m_CosPsi, 0);
    Vec3::Rotate(worldNormalRot, m_SinTheta, m_CosTheta, 1);
    Vec3::Rotate(worldNormalRot, m_SinPhi, m_CosPhi, 2);

    res.WorldLocation = worldLocationRot + m_WorldLocation;
    res.SetFaceNormal(transformed, worldNormalRot);
    res.SetFaceNormal(translated, res.WorldNormal);
    return true;
}

BoundingBox TraceableComponent::GetBoundingBox() const {
    return BoundingBox(m_RotatedBoundingBox.MinBound + m_WorldLocation,
                       m_RotatedBoundingBox.MaxBound + m_WorldLocation);
}
