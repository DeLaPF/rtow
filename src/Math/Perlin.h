#pragma once

#include "Math/Vec.h"

class Perlin {
public:
    Perlin();
    ~Perlin();

    double Noise(const Vec3& point) const;

    double Turbulence(const Vec3& point, uint32_t depth) const;
private:
    static double PerlinInterp(Vec3 c[2][2][2], double u, double v, double w);
private:
    const size_t m_NumPoints;
    Vec3* m_RandVecs;
    uint32_t* m_PerumationsX;
    uint32_t* m_PerumationsY;
    uint32_t* m_PerumationsZ;
};
