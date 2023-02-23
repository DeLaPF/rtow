#include "Scene.h"

void Scene::addComponent(std::shared_ptr<SceneComponent> component) {
    if (auto traceableComponent = std::dynamic_pointer_cast<TraceableComponent>(component)) {
        m_TraceableComponents.push_back(traceableComponent);
    } else {
        m_SceneComponents.push_back(component);
    }
}

std::shared_ptr<SceneComponent> Scene::GetComponentAt(int index) const {
    if (index < 0 || index >= m_SceneComponents.size()) {
        return std::make_shared<SceneComponent>(SceneComponent());
    }

    return m_SceneComponents.at(index);
}

std::shared_ptr<TraceableComponent> Scene::GetTraceableComponentAt(int index) const {
    if (index < 0 || index >= m_TraceableComponents.size()) {
        return std::make_shared<TraceableComponent>(TraceableComponent());
    }

    return m_TraceableComponents.at(index);
}

std::shared_ptr<Material> Scene::GetMaterial(int index) const {
    if (index < 0 || index >= m_Materials.size()) {
        return std::make_shared<Material>(Material());
    }

    return m_Materials.at(index);
}

bool Scene::RayCast(const Ray& ray, double distMin, double distMax, TraceResult& res) const {
    double nearestHit = distMax;
    for (size_t i = 0; i < m_TraceableComponents.size(); i++) {
        if (m_TraceableComponents.at(i)->Trace(ray, distMin, nearestHit, res)) {
            nearestHit = res.HitDistance;
            res.HitIndex = (int)i;
        }
    }
    return res.Success;
}

void Scene::GenBoundingVolumeHierarchy() {
    m_TraceableComponents.push_back(std::make_shared<BVHNode>(m_TraceableComponents, 0, m_TraceableComponents.size()));
}
