#pragma once

#include "Material.h"
#include "Scene/BVHNode.h"
#include "TraceableComponent.h"
#include "SceneComponent.h"
#include "Sphere.h"

#include <memory>
#include <vector>

class Scene {
    public:
        Scene() {}

        void addComponent(std::shared_ptr<SceneComponent> component);
        void clearComponents() { m_SceneComponents.clear(); }
        std::shared_ptr<SceneComponent> GetComponentAt(int index) const;
        std::shared_ptr<TraceableComponent> GetTraceableComponentAt(int index) const;

        void addMaterial(std::shared_ptr<Material> material) { m_Materials.push_back(material); }
        void clearMaterials() { m_Materials.clear(); }
        std::shared_ptr<Material> GetMaterial(int index) const;

        bool RayCast(const Ray& ray, double distMin, double distMax, TraceResult& res) const;

        void GenBoundingVolumeHierarchy();
    private:
        std::vector<std::shared_ptr<SceneComponent>> m_SceneComponents;
        std::vector<std::shared_ptr<TraceableComponent>> m_TraceableComponents;
        std::vector<std::shared_ptr<Material>> m_Materials;
    public:
        static Scene GenRandomScene();
};
