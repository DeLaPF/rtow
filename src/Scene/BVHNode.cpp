#include "Scene/BVHNode.h"

BVHNode::BVHNode(std::vector<std::shared_ptr<TraceableComponent>>& components, size_t startInd, size_t endInd)
        : StartInd(startInd), EndInd(endInd) {
    switch (endInd - startInd) {
    case 1:
        Left = Right = components[startInd];
        break;
    case 2:
        Left = std::make_shared<BVHNode>(components, startInd + 1, endInd);
        Right = std::make_shared<BVHNode>(components, startInd, startInd + 1);
        break;
    default:
        size_t mid = startInd + ((endInd - startInd) / 2);
        Left = std::make_shared<BVHNode>(components, startInd, mid);
        Right = std::make_shared<BVHNode>(components, mid, endInd);
    };

    m_BoundingBox = BoundingBox::Surrounding(Left->GetBoundingBox(), Right->GetBoundingBox());
}

bool BVHNode::Trace(const Ray &ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    if (!m_BoundingBox.DoesOverlap(ray, traceDistMin, traceDistMax)) { return false; }
    if (EndInd - StartInd == 1) {
        if (Left->Trace(ray, traceDistMin, traceDistMax, res)) {
            res.HitComponentIndex = StartInd;
            return true;
        }
        return false;
    }

    bool left = Left->Trace(ray, traceDistMin, traceDistMax, res);
    bool right = Right->Trace(ray, traceDistMin, left ? res.HitDistance : traceDistMax, res);
    return left || right;
}
