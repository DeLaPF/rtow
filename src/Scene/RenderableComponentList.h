#pragma once

#include "RenderableComponent.h"

#include <memory>
#include <vector>

class RenderableComponentList {
public:
    RenderableComponentList() {}

    size_t size() const { return m_RenderableComponents.size(); }

    void addComponent(std::shared_ptr<RenderableComponent> component) { m_RenderableComponents.push_back(component); }
    void clearComponents() { m_RenderableComponents.clear(); }
    std::shared_ptr<RenderableComponent> GetComponent(int index) const { return m_RenderableComponents.at(index); }

    HitResult GetHitResult(const Ray& ray, double distMin, double distMax) const;
private:
    std::vector<std::shared_ptr<RenderableComponent>> m_RenderableComponents;
};
