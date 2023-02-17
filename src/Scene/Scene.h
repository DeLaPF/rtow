#pragma once

#include "Material.h"
#include "SceneComponent.h"

#include <memory>
#include <vector>

class Scene {
    public:
        Scene() {}

        void addComponent(std::shared_ptr<SceneComponent> component) { m_Components.push_back(component); }
        void clearComponents() { m_Components.clear(); }
        std::shared_ptr<SceneComponent> GetComponent(int index) const;

        void addMaterial(std::shared_ptr<Material> material) { m_Materials.push_back(material); }
        void clearMaterials() { m_Materials.clear(); }
        std::shared_ptr<Material> GetMaterial(int index) const;

        HitResult RayCast(const Ray& ray, double distMin, double distMax) const;
    public:
        std::vector<std::shared_ptr<SceneComponent>> m_Components;
        std::vector<std::shared_ptr<Material>> m_Materials;
};
