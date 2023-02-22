#pragma once

#include "BoundingVolume.h"
#include "TraceableComponent.h"
#include "Math/Random.h"

#include <algorithm>
#include <memory>
#include <vector>

class BVHNode : public TraceableComponent {
public:
    BVHNode(std::vector<std::shared_ptr<TraceableComponent>>& components, size_t startInd, size_t endInd) {
        auto children = components;
        size_t numChildren = endInd - startInd;
        int axis = Random::Int(0, 2);
        auto comparator = (axis == 0) ? BoxCompareX
                        : (axis == 1) ? BoxCompareY
                                      : BoxCompareZ;

        if (numChildren >= 2) {
            Left = Right = children[startInd];
            if (numChildren == 2) {
                if (comparator(children[startInd], children[startInd + 1])) {
                    Right = children[startInd + 1];
                } else {
                    Left = children[startInd + 1];
                }
            }
        } else {
            std::sort(children.begin() + startInd, children.begin() + endInd, comparator);
            size_t mid = startInd + numChildren/2;
            Left = std::make_shared<BVHNode>(children, startInd, mid);
            Right = std::make_shared<BVHNode>(children, mid, endInd);
        }

        m_BoundingBox = BoundingBox::Surrounding(Left->GetBoundingBox(), Right->GetBoundingBox());
    }

    virtual bool Trace(const Ray &ray, double traceDistMin, double traceDistMax, TraceResult& res) const override {
        if (!m_BoundingBox.DoesOverlap(ray, traceDistMin, traceDistMax)) { return false; }

        bool left = Left->Trace(ray, traceDistMin, traceDistMax, res);
        bool right = Right->Trace(ray, traceDistMin, left ? res.HitDistance : traceDistMax, res);
        return left || right;
    }

    virtual BoundingBox GetBoundingBox() const override {
        return m_BoundingBox;
    }
private:
    static inline bool BoxCompare(const std::shared_ptr<TraceableComponent> a, const std::shared_ptr<TraceableComponent> b, int axis) {
        return a->GetBoundingBox().MinBound[axis] < b->GetBoundingBox().MinBound[axis];
    }

    static bool BoxCompareX(const std::shared_ptr<TraceableComponent> a, const std::shared_ptr<TraceableComponent> b) {
        return BoxCompare(a, b, 0);
    }

    static bool BoxCompareY(const std::shared_ptr<TraceableComponent> a, const std::shared_ptr<TraceableComponent> b) {
        return BoxCompare(a, b, 1);
    }

    static bool BoxCompareZ(const std::shared_ptr<TraceableComponent> a, const std::shared_ptr<TraceableComponent> b) {
        return BoxCompare(a, b, 2);
    }
public:
    std::shared_ptr<TraceableComponent> Left;
    std::shared_ptr<TraceableComponent> Right;
private:
    BoundingBox m_BoundingBox;
};
