#pragma once

#include "Math/Vec.h"

#include <cmath>
#include <memory>

class Texture {
public:
    Texture() : m_Color(Vec3()) {}
    Texture(Vec3 color) : m_Color(color) {}
    
    virtual Vec3 Value(const Vec2& UV, const Vec3& point) const { return m_Color; }

protected:
    Vec3 m_Color;
};

class CheckeredTexture: public Texture {
public:
    CheckeredTexture() {}

    CheckeredTexture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd)
        : even(_even), odd(_odd) {}

    CheckeredTexture(Vec3 c1, Vec3 c2)
        : even(std::make_shared<Texture>(c1)) , odd(std::make_shared<Texture>(c2)) {}

    virtual Vec3 Value(const Vec2& UV, const Vec3& point) const override {
        double sines = std::sin(10 * point.X) *
                       std::sin(10 * point.Y) *
                       std::sin(10 * point.Z);
        return sines < 0 ? odd->Value(UV, point) : even->Value(UV, point);
    }
public:
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;
};