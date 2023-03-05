#include "Scene/Scene.h"

#include <algorithm>

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
    size_t startInd = 0;
    if (m_BVH) {
        m_BVH->Trace(ray, distMin, distMax, res);
        startInd = m_BVH->EndInd;
    }

    double nearestHit = distMax;
    for (size_t i = startInd; i < m_TraceableComponents.size(); i++) {
        if (m_TraceableComponents.at(i)->Trace(ray, distMin, nearestHit, res)) {
            res.HitComponentIndex = i;
            nearestHit = res.HitDistance;
        }
    }
    return res.Success;
}

void Scene::GenBoundingVolumeHierarchy() {
    SortComponentsForBVH(0, m_TraceableComponents.size());
    m_BVH = std::make_unique<BVHNode>(m_TraceableComponents, 0, m_TraceableComponents.size());
}

void Scene::SortComponentsForBVH(size_t startInd, size_t endInd) {
    if (endInd - startInd == 1) { return; }

    int axis = Random::Int(0, 2);
    auto comparator = TraceableComponentComparator(axis);
    std::sort(m_TraceableComponents.begin() + startInd, m_TraceableComponents.begin() + endInd, comparator);
    size_t mid = startInd + ((endInd - startInd) / 2);
    SortComponentsForBVH(startInd, mid);
    SortComponentsForBVH(mid, endInd);
}
