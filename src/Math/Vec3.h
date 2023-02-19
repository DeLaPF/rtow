#pragma once

#include "Random.h"

#include <cmath>
#include <iostream>
#include <sstream>

class Vec {
public:
    Vec() : X(0.0), size(1) {
        vec = &X;
    }
    Vec(double x) : X(x), size(1) {
        vec = &X;
    }

    size_t length() const { return size; }

    double operator[](int i) const { return vec[i]; }
    double& operator[](int i) { return vec[i]; }
    void operator=(const Vec& v) const {
        for (size_t i = 0; i < size && i < v.length(); i++) { vec[i] = v[i]; }
    }
    Vec operator-() const {
        Vec res = Vec(size);
        for (size_t i = 0; i < size; i++) { res[i] = -vec[i]; }
        return res;
    }
    auto& operator+=(const Vec& v) {
        for (size_t i = 0; i < size && i < v.size; i++) { vec[i] += v[i]; }
        return *this;
    }
    auto& operator*=(const double t) {
        for (size_t i = 0; i < size; i++) { vec[i] *= t; }
        return *this;
    }
    auto& operator/=(const double t) {
        for (size_t i = 0; i < size; i++) { vec[i] /= t; }
        return *this;
    }
public:
    union {
        struct {
            double X;
        };
        struct {
            double R;
        };
    };
protected:
    size_t size;
    double* vec;
};

class Vec2 : public Vec {
public:
    Vec2() : X(0.0), Y(0.0) {
        size = 2;
        vec = &X;
    }
    Vec2(double x, double y) : X(0.0), Y(0.0) {
        size = 2;
        vec = &X;
    }

    Vec2 operator-() const {
        Vec2 res = Vec2();
        for (size_t i = 0; i < size; i++) { res[i] = -vec[i]; }
        return res;
    }
public:
    union {
        struct {
            double X, Y;
        };
        struct {
            double R, G;
        };
    };
};

class Vec3 : public Vec {
public:
    Vec3() : X(0.0), Y(0.0), Z(0.0) {
        size = 3;
        vec = &X;
    }
    Vec3(double x, double y, double z) :  X(x), Y(y), Z(z) {
        size = 3;
        vec = &X;
    }

    Vec3 operator-() const {
        Vec3 res = Vec3();
        for (size_t i = 0; i < size; i++) { res[i] = -vec[i]; }
        return res;
    }
public:
    union {
        struct {
            double X, Y, Z;
        };
        struct {
            double R, G, B;
        };
    };
};

class Vec4 : public Vec {
public:
    Vec4() : X(0.0), Y(0.0), Z(0.0), W(0.0) {
        size = 4;
        vec = &X;
    }
    Vec4(double x, double y, double z, double w) :  X(x), Y(y), Z(z), W(w) {
        size = 4;
        vec = &X;
    }

    Vec4 operator-() const {
        Vec4 res = Vec4();
        for (size_t i = 0; i < size; i++) { res[i] = -vec[i]; }
        return res;
    }
public:
    union {
        struct {
            double X, Y, Z, W;
        };
        struct {
            double R, G, B, A;
        };
    };
};

// TODO: generalize input and output for all below to all Vec classes
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    std::ostringstream oss;
    for (size_t i = 0; i < v.length(); i++) {
        oss << v[i] << ", ";
    }
    return out << oss.str();
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    double vec[4] = { 0.0, 0.0, 0.0, 0.0 };
    for (size_t i = 0; i < u.length(); i++) { vec[i] = u[i]; }
    for (size_t i = 0; i < v.length(); i++) { vec[i] += v[i]; }

    return Vec3(vec[0], vec[1], vec[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.X - v.X, u.Y - v.Y, u.Z - v.Z);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.X * v.X, u.Y * v.Y, u.Z * v.Z);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.X, t*v.Y, t*v.Z);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

// Utility Functions
namespace Vec3Util {
    inline double dot(const Vec3 &u, const Vec3 &v) {
        return u.X * v.X
             + u.Y * v.Y
             + u.Z * v.Z;
    }

    inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.Y * v.Z - u.Z * v.Y,
                    u.Z * v.X - u.X * v.Z,
                    u.X * v.Y - u.Y * v.X);
    }

    inline Vec3 normalize(Vec3 v) {
        return v / std::sqrt(dot(v, v));
    }

    inline Vec3 reflect(const Vec3& v, const Vec3& reflectionAxis) {
        return v - (2 * (dot(v, reflectionAxis) * reflectionAxis));
    }

    inline Vec3 random(double min, double max) {
        return normalize(Vec3(Random::Double(min, max), Random::Double(min, max), Random::Double(min, max)));
    }

    inline Vec3 random() {
        return random(-1, 1);
    }

    inline Vec3 randomInDisk() {
        return normalize(Vec3(Random::Double(-1, 1), Random::Double(-1, 1), 0.0));
    }

    inline Vec3 randomBounce(const Vec3& normal) {
        Vec3 rand = random();
        if (dot(rand, normal) <= 0.0) {
            rand = -rand;
        }

        return rand;
    }
}
