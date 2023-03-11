#include "Scene/AxisAlignedBox.h"

#include "Scene/AxisAlignedRect.h"

Box::Box()
        : TraceableComponent(),
          MinBound(Vec3()), MaxBound(Vec3(1)) {
    Setup(Vec3(), Vec3(), Vec3(), 0);
}
Box::Box(Vec3 location, Vec3 dimensions, int materialIndex)
        : TraceableComponent(location, materialIndex),
          MinBound(0, 0, 0), MaxBound(dimensions) {
    Setup(location, dimensions, Vec3(), materialIndex);
}
Box::Box(Vec3 location, Vec3 dimensions, Vec3 rotation, int materialIndex)
        : TraceableComponent(location, materialIndex),
          MinBound(0, 0, 0), MaxBound(dimensions) {
    Setup(location, dimensions, rotation, materialIndex);
}

bool Box::TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
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

void Box::Setup(Vec3 location, Vec3 dimensions, Vec3 rotation, int materialIndex) {
    SetWorldLocation(location);
    SetWorldRotation(rotation);

    Sides.push_back(std::make_shared<RectXY>(Vec3(0, 0, 0), Vec2(dimensions.X, dimensions.Y), materialIndex));
    Sides.push_back(std::make_shared<RectXY>(Vec3(0, 0, dimensions.Z), Vec2(dimensions.X, dimensions.Y), materialIndex));

    Sides.push_back(std::make_shared<RectXZ>(Vec3(0, 0, 0), Vec2(dimensions.X, dimensions.Z), materialIndex));
    Sides.push_back(std::make_shared<RectXZ>(Vec3(0, dimensions.Y, 0), Vec2(dimensions.X, dimensions.Z), materialIndex));

    Sides.push_back(std::make_shared<RectYZ>(Vec3(0, 0, 0), Vec2(dimensions.Y, dimensions.Z), materialIndex));
    Sides.push_back(std::make_shared<RectYZ>(Vec3(dimensions.X, 0, 0), Vec2(dimensions.Y, dimensions.Z), materialIndex));
}
