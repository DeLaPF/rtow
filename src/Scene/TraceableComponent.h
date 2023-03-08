#pragma once

#include <limits>
#include <memory>

#include "Math/Vec.h"
#include "Scene/BoundingVolume.h"
#include "Scene/SceneComponent.h"
#include "Scene/Traceable.h"

class TraceableComponent : public SceneComponent, Traceable {
public:
    TraceableComponent() : SceneComponent() {}
    TraceableComponent(Vec3 location, int materialIndex)
        : SceneComponent(location, materialIndex) {}
    TraceableComponent(Vec3 location, Vec3 rotation, int materialIndex)
        : SceneComponent(location, rotation, materialIndex) {}

    virtual void SetWorldRotation(Vec3 rotation) override {
        SceneComponent::SetWorldRotation(rotation);

        BoundingBox bounding = GetBoundingBoxImpl();
        Rotate(bounding, m_SinPsi, m_CosPsi, 0);
        Rotate(bounding, m_SinTheta, m_CosTheta, 1);
        Rotate(bounding, m_SinPhi, m_CosPhi, 2);
        m_RotatedBoundingBox = bounding;
    }

    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override {
        // TODO: do the other two axis negate cos instead of sin?
        Vec3 originInvRot = ray.Origin - m_WorldLocation;
        Rotate(originInvRot, -m_SinPhi, m_CosPhi, 2);
        Rotate(originInvRot, -m_SinTheta, m_CosTheta, 1);
        Rotate(originInvRot, -m_SinPsi, m_CosPsi, 0);
        Vec3 directionInvRot = ray.Direction;
        Rotate(directionInvRot, -m_SinPhi, m_CosPhi, 2);
        Rotate(directionInvRot, -m_SinTheta, m_CosTheta, 1);
        Rotate(directionInvRot, -m_SinPsi, m_CosPsi, 0);

        Ray translated = Ray(ray.Origin - m_WorldLocation, ray.Direction);
        Ray transformed = Ray(originInvRot, directionInvRot);
        if (!TraceImpl(transformed, traceDistMin, traceDistMax, res)) { return false; }

        Vec3 worldLocationRot = res.WorldLocation;
        Rotate(worldLocationRot, m_SinPsi, m_CosPsi, 0);
        Rotate(worldLocationRot, m_SinTheta, m_CosTheta, 1);
        Rotate(worldLocationRot, m_SinPhi, m_CosPhi, 2);
        Vec3 worldNormalRot = res.WorldNormal;
        Rotate(worldNormalRot, m_SinPsi, m_CosPsi, 0);
        Rotate(worldNormalRot, m_SinTheta, m_CosTheta, 1);
        Rotate(worldNormalRot, m_SinPhi, m_CosPhi, 2);

        res.WorldLocation = worldLocationRot + m_WorldLocation;
        res.SetFaceNormal(transformed, worldNormalRot);
        res.SetFaceNormal(translated, res.WorldNormal);
        return true;
    }

    virtual BoundingBox GetBoundingBox() const override {
        return BoundingBox(m_RotatedBoundingBox.MinBound + m_WorldLocation,
                           m_RotatedBoundingBox.MaxBound + m_WorldLocation);
    }

    virtual bool TraceImpl(const Ray& ray, double traceDistMin,
            double traceDistMax, TraceResult& res) const { return false; }
    virtual BoundingBox GetBoundingBoxImpl() const { return BoundingBox(); }
private:
    // TODO: pull out into BoundingBox class
    void Rotate(BoundingBox& bounding, double sinA, double cosA, size_t axis) const {
        Vec3 min = Vec3(std::numeric_limits<double>::max());
        Vec3 max = Vec3(std::numeric_limits<double>::min());
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    double x = (i * bounding.MaxBound.X) + ((1 - i) * bounding.MinBound.X);
                    double y = (j * bounding.MaxBound.Y) + ((1 - j) * bounding.MinBound.Y);
                    double z = (k * bounding.MaxBound.Z) + ((1 - k) * bounding.MinBound.Z);

                    Vec3 corner = Vec3(x, y, z);
                    Rotate(corner, sinA, cosA, axis);
                    for (int c = 0; c < 3; c++) {
                        min[c] = std::fmin(min[c], corner[c]);
                        max[c] = std::fmax(max[c], corner[c]);
                    }
                }
            }
        }

        bounding = BoundingBox(min, max);
    }

    void Rotate(Vec3& vec, double sinA, double cosA, size_t axis) const {
        Vec3 temp = vec;
        switch (axis) {
        case 0:
            vec.Y = (cosA * temp.Y) + (-sinA * temp.Z);
            vec.Z = (sinA * temp.Y) + (cosA * temp.Z);
            break;
        case 1:
            vec.X = (cosA * temp.X) + (sinA * temp.Z);
            vec.Z = (-sinA * temp.X) + (cosA * temp.Z);
            break;
        case 2:
            vec.X = (cosA * temp.X) + (-sinA * temp.Y);
            vec.Y = (sinA * temp.X) + (cosA * temp.Y);
            break;
        }
    }
private:
    BoundingBox m_RotatedBoundingBox;
};

class TraceableComponentComparator {
public:
    TraceableComponentComparator(uint32_t axis)
        : m_BBComparator(BoundingBoxComparator(axis)) {}

    bool operator()(const TraceableComponent& a, const TraceableComponent& b) {
        return m_BBComparator(a.GetBoundingBox(), b.GetBoundingBox());
    }
    bool operator()(const std::shared_ptr<TraceableComponent>& a,
                    const std::shared_ptr<TraceableComponent>& b) {
        return m_BBComparator(a->GetBoundingBox(), b->GetBoundingBox());
    }
private:
    BoundingBoxComparator m_BBComparator;
};
