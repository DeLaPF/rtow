#pragma once

#include <random>

inline double RandomDouble() {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    thread_local std::mt19937 generator(std::random_device{}());
    return distribution(generator);
}

inline double RandomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + ((max - min) * RandomDouble());
}
