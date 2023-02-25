#pragma once

#include "Random.h"

#include <sstream>

template <int SIZE>
class Vec {
public:
static_assert(SIZE > 1 && SIZE <= 4, "Error: Vec<SIZE>, SIZE must be 2, 3, or 4");
    Vec() : X(0), Y(0), Z(0), W(0) { vec = &X; }
    Vec(double v) : X(v), Y(v), Z(v), W(v) { vec = &X; }
    Vec(double x, double y) : X(x), Y(y), Z(0), W(0) { vec = &X; }
    Vec(double x, double y, double z) : X(x), Y(y), Z(z), W(0) { vec = &X; }
    Vec(double x, double y, double z, double w) : X(x), Y(y), Z(z), W(w) { vec = &X; }
    template <int N>
    Vec(const Vec<N>& v) : X(v.X), Y(v.Y), Z(v.Z), W(v.W) { vec = &X; }

    double length() const { return std::sqrt(lengthSquared()); }
    double lengthSquared() const { return dot(*this, *this); }

    double operator[](int i) const { return vec[i]; }
    double& operator[](int i) { return vec[i]; }
    void operator=(const Vec& v) { X = v.X, Y = v.Y, Z = v.Z, W = v.W; }
    Vec operator-() const { return Vec<SIZE>(-X, -Y, -Z, -W); }
    template <int N>
    Vec& operator+=(const Vec<N>& v) {
        X += v.X, Y += v.Y, Z += v.Z, W += v.W;
        return *this;
    }
    Vec& operator*=(const double t) {
        X *= t, Y *= t, Z *= t, W *= t;
        return *this;
    }
    Vec& operator/=(const double t) {
        X /= t, Y /= t, Z /= t, W /= t;
        return *this;
    }
public:
    union {
        struct { double X, Y, Z, W; };
        struct { double R, G, B, A; };
    };
    const size_t size = SIZE;
protected:
    double* vec;
public:
    static inline double dot(const Vec<SIZE> &u, const Vec<SIZE> &v) {
        return u.X * v.X + u.Y * v.Y + u.Z * v.Z + u.W * v.W;
    }

    static inline Vec<SIZE> normalize(Vec<SIZE> v) { return v / v.length(); }

    static inline Vec<SIZE> random(double min, double max) {
        return Vec<SIZE>::normalize(Vec<SIZE>(Random::Double(min, max),
                                              Random::Double(min, max),
                                              Random::Double(min, max),
                                              Random::Double(min, max)));
    }

    static inline Vec<SIZE> random() { return Vec<SIZE>::random(-1, 1); }

    static inline Vec<SIZE> reflect(const Vec<SIZE>& v, const Vec<SIZE>& reflectionAxis) {
        return v - (2 * (Vec<SIZE>::dot(v, reflectionAxis) * reflectionAxis));
    }

    static inline Vec<SIZE> randomBounce(const Vec<SIZE>& normal) {
        Vec<SIZE> rand = Vec<SIZE>::random();
        if (Vec<SIZE>::dot(rand, normal) <= 0.0) {
            rand = -rand;
        }

        return rand;
    }

    static inline Vec<SIZE> cross(const Vec<SIZE>& u, const Vec<SIZE>& v) {
        return Vec<SIZE>(u.Y * v.Z - u.Z * v.Y,
                         u.Z * v.X - u.X * v.Z,
                         u.X * v.Y - u.Y * v.X);
    }
};

using Vec2 = Vec<2>;
using Vec3 = Vec<3>;
using Vec4 = Vec<4>;

template <int SIZE>
inline std::ostream& operator<<(std::ostream& out, const Vec<SIZE>& v) {
    out << v[0];
    for (size_t i = 0; i < v.size; i++) { out << ", " << v[i]; }
    return out;
}

template <int SIZE1, int SIZE2>
inline Vec<SIZE1> operator+(const Vec<SIZE1>& u, const Vec<SIZE2>& v) {
    return Vec<SIZE1>(u.X + v.X, u.Y + v.Y, u.Z + v.Z, u.W + v.W);
}

template <int SIZE1, int SIZE2>
inline Vec<SIZE1> operator-(const Vec<SIZE1>& u, const Vec<SIZE2>& v) {
    return Vec<SIZE1>(u.X - v.X, u.Y - v.Y, u.Z - v.Z, u.W - v.W);
}

template <int SIZE1, int SIZE2>
inline Vec<SIZE1> operator*(const Vec<SIZE1>& u, const Vec<SIZE2>& v) {
    return Vec<SIZE1>(u.X * v.X, u.Y * v.Y, u.Z * v.Z, u.W * v.W);
}

template <int SIZE>
inline Vec<SIZE> operator*(double t, const Vec<SIZE>& v) {
    return Vec<SIZE>(v.X * t, v.Y * t, v.Z * t, v.W * t);
}

template <int SIZE>
inline Vec<SIZE> operator*(const Vec<SIZE>& v, double t) {
    return Vec<SIZE>(v.X * t, v.Y * t, v.Z * t, v.W * t);
}

template <int SIZE>
inline Vec<SIZE> operator/(const Vec<SIZE>& v, double t) {
    return Vec<SIZE>(v.X / t, v.Y / t, v.Z / t, v.W / t);
}
