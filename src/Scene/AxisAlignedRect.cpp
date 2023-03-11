#include "Scene/AxisAlignedRect.h"

template <int TYPE>
Rect<TYPE>::Rect()
        : TraceableComponent() {
    Setup(Vec3(), Vec2(1), Vec3());
}
template <int TYPE>
Rect<TYPE>::Rect(Vec3 location, Vec2 dimensions, int materialIndex)
        : TraceableComponent(location, materialIndex) {
    Setup(location, dimensions, Vec3());
}
template <int TYPE>
Rect<TYPE>::Rect(Vec3 location, Vec2 dimensions, Vec3 rotation, int materialIndex)
        : TraceableComponent(location, rotation, materialIndex) {
    Setup(location, dimensions, rotation);
}

template <int TYPE>
bool Rect<TYPE>::TraceImpl(const Ray& ray, double traceDistMin, double traceDistMax, TraceResult& res) const {
    size_t a, b, c;
    Vec3 normal;
    switch (TYPE) {
    case 0:
        a = 0, b = 1, c = 2; // XY, z
        normal = Vec3 (0, 0, 1);
        break;
    case 1:
        a = 0, b = 2, c = 1; // XZ, y
        normal = Vec3 (0, 1, 0);
        break;
    case 2:
        a = 1, b = 2, c = 0; // YZ, x
        normal = Vec3 (1, 0, 0);
        break;
    }

    // TODO: There's a weird issue/edge case that makes ray.Origin[0] != ray.Origin.X, I need to fix that
    Vec3 origin = ray.Origin * 1;
    Vec3 direction = ray.Direction * 1;
    double t = -origin[c] / direction[c];
    if (t < traceDistMin || t > traceDistMax) { return false; }

    Vec3 planeIntersection = ray.At(t);
    if (planeIntersection[a] < MinBound[a] || planeIntersection[a] > MaxBound[a]) { return false; }
    if (planeIntersection[b] < MinBound[b] || planeIntersection[b] > MaxBound[b]) { return false; }

    res.Success = true;
    res.HitDistance = t;
    res.WorldLocation = planeIntersection;
    res.SetFaceNormal(ray, normal);
    res.ComponentUV = Vec2((planeIntersection[a] - MinBound[a]) / (MaxBound[a] - MinBound[a]),
                           (planeIntersection[b] - MinBound[b]) / (MaxBound[b] - MinBound[b]));
    return true;
}

template <int TYPE>
void Rect<TYPE>::Setup(Vec3 location, Vec2 dimensions, Vec3 rotation) {
    switch (TYPE) {
    case 0:
        MinBound = Vec3(0, 0, -0.0001);
        MaxBound = Vec3(dimensions[0], dimensions[1], location.Z + 0.0001);
        break;
    case 1:
        MinBound = Vec3(0, -0.0001, 0);
        MaxBound = Vec3(dimensions[0], location.Y + 0.0001, dimensions[1]);
        break;
    case 2:
        MinBound = Vec3(-0.0001, 0, 0);
        MaxBound = Vec3(location.X + 0.0001, dimensions[0], dimensions[1]);
        break;
    }
    SetWorldLocation(location);
    SetWorldRotation(rotation);
}

template class Rect<0>;
template class Rect<1>;
template class Rect<2>;
