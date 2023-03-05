#include "Scene/AxisAlignedBox.h"

#include "Scene/AxisAlignedRect.h"

Box::Box(Vec3 minBound, Vec3 maxBound, int materialIndex)
        : TraceableComponent(Vec3(minBound.X, maxBound.Y, maxBound.Z), materialIndex),
          MinBound(minBound), MaxBound(maxBound) {
    Sides.push_back(std::make_shared<RectXY>(minBound.X, maxBound.X, minBound.Y, maxBound.Y, maxBound.Z, materialIndex));
    Sides.push_back(std::make_shared<RectXY>(minBound.X, maxBound.X, minBound.Y, maxBound.Y, minBound.Z, materialIndex));

    Sides.push_back(std::make_shared<RectXZ>(minBound.X, maxBound.X, minBound.Z, maxBound.Z, maxBound.Y, materialIndex));
    Sides.push_back(std::make_shared<RectXZ>(minBound.X, maxBound.X, minBound.Z, maxBound.Z, minBound.Y, materialIndex));

    Sides.push_back(std::make_shared<RectYZ>(minBound.Y, maxBound.Y, minBound.Z, maxBound.Z, maxBound.X, materialIndex));
    Sides.push_back(std::make_shared<RectYZ>(minBound.Y, maxBound.Y, minBound.Z, maxBound.Z, minBound.X, materialIndex));
}

bool Box::Trace(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    bool success = false;
    double nearestHit = traceDistMax;
    for (size_t i = 0; i < Sides.size(); i++) {
        if (Sides.at(i)->Trace(ray, traceDistMin, nearestHit, res)) {
            nearestHit = res.HitDistance;
            success = true;
        }
    }
    return success;
}
