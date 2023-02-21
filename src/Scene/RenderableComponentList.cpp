#include "RenderableComponentList.h"

HitResult RenderableComponentList::GetHitResult(const Ray& ray, double distMin, double distMax) const {
    HitResult res;

    double nearestHit = distMax;
    for (size_t i = 0; i < m_RenderableComponents.size(); i++) {
        HitResult temp = m_RenderableComponents.at(i)->GetHitResult(ray, distMin, nearestHit);
        if (temp.DidHit) {
            nearestHit = temp.HitDistance;
            res = temp;
            res.HitIndex = (int)i;
        }
    }

    return res;
}
