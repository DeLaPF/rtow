#include "Scene.h"

HitResult Scene::RayCast(const Ray& r, double distMin, double distMax) const {
    HitResult res;

    double nearestHit = distMax;
    for (const auto& component : Components) {
        HitResult temp = component->Hit(r, distMin, nearestHit);
        if (temp.DidHit) {
            nearestHit = temp.HitDistance;
            res = temp;
        }
    }

    return res;
}
