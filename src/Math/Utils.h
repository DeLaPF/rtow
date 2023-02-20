#pragma once

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
};
