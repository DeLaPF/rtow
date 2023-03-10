#pragma once

#include <memory>
#include <vector>

#include "Scene/BoundingVolume.h"
#include "Scene/TraceableComponent.h"

class BVHNode : public TraceableComponent {
public:
    BVHNode(std::vector<std::shared_ptr<TraceableComponent>>& components, size_t startInd, size_t endInd);

    virtual bool Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const override;

    virtual BoundingBox GetBoundingBox() const override { return m_BoundingBox; }
public:
    std::shared_ptr<TraceableComponent> Left;
    std::shared_ptr<TraceableComponent> Right;
    uint32_t StartInd;
    uint32_t EndInd;
private:
    BoundingBox m_BoundingBox;
};
