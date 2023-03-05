#pragma once

#include "Math/Random.h"

namespace Utils {
    const double PI = 3.1415926535897932385;

    inline double clamp(double x, double min, double max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    inline double degreesToRadians(double degrees) {
        return degrees * PI / 180.0;
    }

    template <typename T>
    inline void PermuteArray(T* array, size_t length) {
        for (size_t i = 0; i < length; i++) {
            std::swap(array[i], array[Random::Int(0, i)]);
        }
    }
};
