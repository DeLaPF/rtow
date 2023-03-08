#pragma once

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

    virtual void SetWorldRotation(Vec3 rotation) override;

    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBox() const override;

    virtual bool TraceImpl(const Ray& ray, double traceDistMin,
            double traceDistMax, TraceResult& res) const { return false; }
    virtual BoundingBox GetBoundingBoxImpl() const { return BoundingBox(); }
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
