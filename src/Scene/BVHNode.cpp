#include "Scene/BVHNode.h"

#include <algorithm>

#include "Math/Random.h"
#include "Scene/TraceableComponent.h"

BVHNode::BVHNode(std::vector<std::shared_ptr<TraceableComponent>>& components, size_t startInd, size_t endInd) {
    auto children = components;
    size_t numChildren = endInd - startInd;
    int axis = Random::Int(0, 2);
    auto comparator = TraceableComponentComparator(axis);

    if (numChildren <= 2) {
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
        size_t mid = startInd + (numChildren / 2);
        Left = std::make_shared<BVHNode>(children, startInd, mid);
        Right = std::make_shared<BVHNode>(children, mid, endInd);
    }

    m_BoundingBox = BoundingBox::Surrounding(Left->GetBoundingBox(), Right->GetBoundingBox());
}

bool BVHNode::Trace(const Ray &ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    if (!m_BoundingBox.DoesOverlap(ray, traceDistMin, traceDistMax)) { return false; }

    bool left = Left->Trace(ray, traceDistMin, traceDistMax, res);
    bool right = Right->Trace(ray, traceDistMin, left ? res.HitDistance : traceDistMax, res);
    return left || right;
}
