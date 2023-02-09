#pragma once

#include "Ray.h"
#include "Vec3.h"

namespace Utils {
    inline Vec3 locationAt(const Ray& ray, double t) { return ray.Origin + (t * ray.Direction); }

    inline double clamp(double x, double min, double max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
};
