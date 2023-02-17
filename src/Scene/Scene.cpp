#include "Scene.h"

std::shared_ptr<SceneComponent> Scene::GetComponent(int index) const {
    if (m_Components.size() <= index || index < 0) {
        return std::make_shared<SceneComponent>(SceneComponent());
    }

    return m_Components.at(index);
}

std::shared_ptr<Material> Scene::GetMaterial(int index) const {
    if (m_Materials.size() <= index || index < 0) {
        return std::make_shared<Material>(Material());
    }

    return m_Materials.at(index);
}

HitResult Scene::RayCast(const Ray& ray, double distMin, double distMax) const {
    HitResult res;

    double nearestHit = distMax;
    for (size_t i = 0; i < m_Components.size(); i++) {
        HitResult temp = m_Components.at(i)->GetHitResult(ray, distMin, nearestHit);
        if (temp.DidHit) {
            nearestHit = temp.HitDistance;
            res = temp;
            res.HitIndex = (int)i;
        }
    }

    return res;
}
