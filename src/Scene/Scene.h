#pragma once

#include "SceneComponent.h"

#include <memory>
#include <vector>

class Scene {
    public:
        Scene() {}
        Scene(std::shared_ptr<SceneComponent> object) { addComponent(object); }

        void clearComponents() { Components.clear(); }
        void addComponent(std::shared_ptr<SceneComponent> component) { Components.push_back(component); }

        HitResult RayCast(const Ray& r, double distMin, double distMax) const;

    public:
        std::vector<std::shared_ptr<SceneComponent>> Components;
};
