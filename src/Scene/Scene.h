#pragma once

#include "Material.h"
#include "RenderableComponentList.h"
#include "SceneComponent.h"
#include "Sphere.h"

#include <memory>
#include <vector>

class Scene {
    public:
        Scene() {}

        void addComponent(std::shared_ptr<SceneComponent> component);
        void clearComponents() { m_SceneComponents.clear(); }
        std::shared_ptr<SceneComponent> GetComponent(int index) const;
        std::shared_ptr<RenderableComponent> GetRenderableComponent(int index) const;

        void addMaterial(std::shared_ptr<Material> material) { m_Materials.push_back(material); }
        void clearMaterials() { m_Materials.clear(); }
        std::shared_ptr<Material> GetMaterial(int index) const;

        HitResult RayCast(const Ray& ray, double distMin, double distMax) const;
    public:
        std::vector<std::shared_ptr<SceneComponent>> m_SceneComponents;
        RenderableComponentList m_RenderableComponentList;
        std::vector<std::shared_ptr<Material>> m_Materials;
    public:
        static Scene GenRandomScene();
};
