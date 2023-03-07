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

    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override {
        Ray translated = Ray(ray.Origin - m_WorldLocation, ray.Direction);
        if (!TraceImpl(translated, traceDistMin, traceDistMax, res)) { return false; }

        res.WorldLocation += m_WorldLocation;
        res.SetFaceNormal(translated, res.WorldNormal);
        return true;
    }

    virtual BoundingBox GetBoundingBox() const override {
        BoundingBox bounding = GetBoundingBoxImpl();
        return BoundingBox(bounding.MinBound + m_WorldLocation,
                           bounding.MaxBound + m_WorldLocation);
    }

    virtual bool TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
        return false;
    }

    virtual BoundingBox GetBoundingBoxImpl() const {
        return BoundingBox();
    }
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
