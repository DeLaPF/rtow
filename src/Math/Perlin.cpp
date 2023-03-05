#include "Perlin.h"

#include "Math/Random.h"
#include "Math/Utils.h"

Perlin::Perlin() : m_NumPoints(256) {
    m_RandVecs = new Vec3[m_NumPoints];
    m_PerumationsX = new uint32_t[m_NumPoints];
    m_PerumationsY = new uint32_t[m_NumPoints];
    m_PerumationsZ = new uint32_t[m_NumPoints];

    for (size_t i = 0; i < m_NumPoints; i++) {
        m_RandVecs[i] = Vec3::random();
        m_PerumationsX[i] = i;
        m_PerumationsY[i] = i;
        m_PerumationsZ[i] = i;
    }

    Utils::PermuteArray(m_PerumationsX, m_NumPoints);
    Utils::PermuteArray(m_PerumationsY, m_NumPoints);
    Utils::PermuteArray(m_PerumationsZ, m_NumPoints);
}

Perlin::~Perlin() {
    delete[] m_RandVecs;
    delete[] m_PerumationsX;
    delete[] m_PerumationsY;
    delete[] m_PerumationsZ;
}

double Perlin::Noise(const Vec3& point) const {
    double u = point.X - std::floor(point.X);
    double v = point.Y - std::floor(point.Y);
    double w = point.Z - std::floor(point.Z);
    size_t i = static_cast<size_t>(std::floor(point.X));
    size_t j = static_cast<size_t>(std::floor(point.Y));
    size_t k = static_cast<size_t>(std::floor(point.Z));
    Vec3 c[2][2][2];

    for (int di=0; di < 2; di++) {
        for (int dj=0; dj < 2; dj++) {
            for (int dk=0; dk < 2; dk++) {
                c[di][dj][dk] = m_RandVecs[m_PerumationsX[(i+di) % m_NumPoints] ^
                                           m_PerumationsY[(j+dj) % m_NumPoints] ^
                                           m_PerumationsZ[(k+dk) % m_NumPoints]];
            }
        }
    }

    return PerlinInterp(c, u, v, w);
}

double Perlin::Turbulence(const Vec3& point, uint32_t depth) const {
    auto accum = 0.0;
    auto tempPoint = point;
    auto weight = 1.0;

    for (uint32_t i = 0; i < depth; i++) {
        accum += weight * Noise(tempPoint);
        weight *= 0.5;
        tempPoint *= 2;
    }

    return std::fabs(accum);
}

double Perlin::PerlinInterp(Vec3 c[2][2][2], double u, double v, double w) {
    double uu = u*u*(3-2*u);
    double vv = v*v*(3-2*v);
    double ww = w*w*(3-2*w);
    double accum = 0.0;

    for (int i=0; i < 2; i++) {
        for (int j=0; j < 2; j++) {
            for (int k=0; k < 2; k++) {
                Vec3 weight_v(u-i, v-j, w-k);
                accum += (i*uu + (1-i)*(1-uu))
                       * (j*vv + (1-j)*(1-vv))
                       * (k*ww + (1-k)*(1-ww))
                       * Vec3::dot(c[i][j][k], weight_v);
            }
        }
    }

    return accum;
}
