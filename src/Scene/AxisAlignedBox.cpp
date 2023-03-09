#include "Scene/AxisAlignedBox.h"

#include "Scene/AxisAlignedRect.h"

Box::Box()
        : TraceableComponent(),
          MinBound(Vec3()), MaxBound(Vec3(1)) {
    SetWorldLocation(Vec3());
    SetWorldRotation(Vec3());

    Sides.push_back(std::make_shared<RectXY>(MinBound.X, MaxBound.X, MinBound.Y, MaxBound.Y, MaxBound.Z, -1));
    Sides.push_back(std::make_shared<RectXY>(MinBound.X, MaxBound.X, MinBound.Y, MaxBound.Y, MinBound.Z, -1));

    Sides.push_back(std::make_shared<RectXZ>(MinBound.X, MaxBound.X, MinBound.Z, MaxBound.Z, MaxBound.Y, -1));
    Sides.push_back(std::make_shared<RectXZ>(MinBound.X, MaxBound.X, MinBound.Z, MaxBound.Z, MinBound.Y, -1));

    Sides.push_back(std::make_shared<RectYZ>(MinBound.Y, MaxBound.Y, MinBound.Z, MaxBound.Z, MaxBound.X, -1));
    Sides.push_back(std::make_shared<RectYZ>(MinBound.Y, MaxBound.Y, MinBound.Z, MaxBound.Z, MinBound.X, -1));
}
Box::Box(Vec3 minBound, Vec3 maxBound, int materialIndex)
        : TraceableComponent(minBound, materialIndex),
          MinBound(0, 0, 0), MaxBound(maxBound - minBound) {
    SetWorldLocation(minBound);
    SetWorldRotation(Vec3());

    Sides.push_back(std::make_shared<RectXY>(MinBound.X, MaxBound.X, MinBound.Y, MaxBound.Y, MaxBound.Z, materialIndex));
    Sides.push_back(std::make_shared<RectXY>(MinBound.X, MaxBound.X, MinBound.Y, MaxBound.Y, MinBound.Z, materialIndex));

    Sides.push_back(std::make_shared<RectXZ>(MinBound.X, MaxBound.X, MinBound.Z, MaxBound.Z, MaxBound.Y, materialIndex));
    Sides.push_back(std::make_shared<RectXZ>(MinBound.X, MaxBound.X, MinBound.Z, MaxBound.Z, MinBound.Y, materialIndex));

    Sides.push_back(std::make_shared<RectYZ>(MinBound.Y, MaxBound.Y, MinBound.Z, MaxBound.Z, MaxBound.X, materialIndex));
    Sides.push_back(std::make_shared<RectYZ>(MinBound.Y, MaxBound.Y, MinBound.Z, MaxBound.Z, MinBound.X, materialIndex));
}
Box::Box(Vec3 minBound, Vec3 maxBound, Vec3 rotation, int materialIndex)
        : TraceableComponent(minBound, materialIndex),
          MinBound(0, 0, 0), MaxBound(maxBound - minBound) {
    SetWorldLocation(minBound);
    SetWorldRotation(rotation);

    Sides.push_back(std::make_shared<RectXY>(MinBound.X, MaxBound.X, MinBound.Y, MaxBound.Y, MaxBound.Z, materialIndex));
    Sides.push_back(std::make_shared<RectXY>(MinBound.X, MaxBound.X, MinBound.Y, MaxBound.Y, MinBound.Z, materialIndex));

    Sides.push_back(std::make_shared<RectXZ>(MinBound.X, MaxBound.X, MinBound.Z, MaxBound.Z, MaxBound.Y, materialIndex));
    Sides.push_back(std::make_shared<RectXZ>(MinBound.X, MaxBound.X, MinBound.Z, MaxBound.Z, MinBound.Y, materialIndex));

    Sides.push_back(std::make_shared<RectYZ>(MinBound.Y, MaxBound.Y, MinBound.Z, MaxBound.Z, MaxBound.X, materialIndex));
    Sides.push_back(std::make_shared<RectYZ>(MinBound.Y, MaxBound.Y, MinBound.Z, MaxBound.Z, MinBound.X, materialIndex));
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
