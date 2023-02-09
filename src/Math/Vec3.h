#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
    public:
        Vec3() : X(0), Y(0), Z(0) {}
        Vec3(double x, double y, double z) : X(x), Y(y), Z(z) {}

        Vec3 operator-() const { return Vec3(-X, -Y, -Z); }
        Vec3& operator+=(const Vec3 &v) {
            X += v.X;
            Y += v.Y;
            Z += v.Z;
            return *this;
        }

        Vec3& operator*=(const double t) {
            X *= t;
            Y *= t;
            Z *= t;
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

    public:
        double X;
        double Y;
        double Z;
};

// Utility Functions
inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.X << ' ' << v.Y << ' ' << v.Z;
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.X + v.X, u.Y + v.Y, u.Z + v.Z);
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
