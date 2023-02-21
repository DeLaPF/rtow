#pragma once

#include "Renderable.h"
#include "SceneComponent.h"

class RenderableComponent : public SceneComponent, Renderable {
public:
    RenderableComponent() : SceneComponent() {}
    RenderableComponent(Vec3 location, int materialIndex) : SceneComponent(location, materialIndex) {}

    HitResult GetHitResult(const Ray &r, double hitDistMin, double hitDistMax) const override { return HitResult{}; }
};
