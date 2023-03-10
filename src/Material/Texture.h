#pragma once

#include <memory>

#include "Material/STBImage.h"
#include "Math/Perlin.h"
#include "Math/Utils.h"
#include "Math/Vec.h"

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

    CheckeredTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
        : m_Even(even), m_Odd(odd) {}

    CheckeredTexture(Vec3 c1, Vec3 c2)
        : m_Even(std::make_shared<Texture>(c1)),
          m_Odd(std::make_shared<Texture>(c2)) {}

    virtual Vec3 Value(const Vec2& UV, const Vec3& point) const override {
        double sines = std::sin(10 * point.X) *
                       std::sin(10 * point.Y) *
                       std::sin(10 * point.Z);
        return sines < 0 ? m_Odd->Value(UV, point) : m_Even->Value(UV, point);
    }
public:
    std::shared_ptr<Texture> m_Odd;
    std::shared_ptr<Texture> m_Even;
};

class PerlinNoiseTexture : public Texture {
public:
    PerlinNoiseTexture() : m_Perlin(Perlin()), m_Scale(1) {}
    PerlinNoiseTexture(double scale) : m_Perlin(Perlin()), m_Scale(scale) {}

    virtual Vec3 Value(const Vec2& UV, const Vec3& point) const override {
        return Vec3(1) * 0.5 * (1 + m_Perlin.Noise(point * m_Scale));
    }
public:
    Perlin m_Perlin;
    double m_Scale;
};

class PerlinTurbulenceTexture : public Texture {
public:
    PerlinTurbulenceTexture()
        : m_Perlin(Perlin()), m_Scale(1), m_TurbulenceDepth(7) {}
    PerlinTurbulenceTexture(double scale)
        : m_Perlin(Perlin()), m_Scale(scale), m_TurbulenceDepth(7) {}
    PerlinTurbulenceTexture(double scale, uint32_t turbulanceDepth)
        : m_Perlin(Perlin()), m_Scale(scale), m_TurbulenceDepth(turbulanceDepth) {}

    virtual Vec3 Value(const Vec2& UV, const Vec3& point) const override {
        return Vec3(1) * m_Perlin.Turbulence(m_Scale * point, m_TurbulenceDepth);
    }
public:
    Perlin m_Perlin;
    double m_Scale;
    uint32_t m_TurbulenceDepth;
};

class MarbleTexture : public Texture {
public:
    MarbleTexture() : m_Perlin(Perlin()), m_Scale(1) {}
    MarbleTexture(double scale) : m_Perlin(Perlin()), m_Scale(scale) {}

    virtual Vec3 Value(const Vec2& UV, const Vec3& point) const override {
        return Vec3(1) * 0.5 * (1 + std::sin(m_Scale * point.Z + (10 * m_Perlin.Turbulence(point, 7))));
    }
public:
    Perlin m_Perlin;
    double m_Scale;
};

class ImageTexture : public Texture {
public:
    ImageTexture() : m_Image(STBImage()) {}
    ImageTexture(const char* filename) : m_Image(STBImage(filename)) {}

    virtual Vec3 Value(const Vec2& UV, const Vec3& point) const override {
        if (!m_Image.Data) { return Vec3(0, 1, 1); }

        // Clamp input texture coordinates to [0,1] x [1,0]
        double u = Utils::clamp(UV.X, 0.0, 1.0);
        double v = 1.0 - Utils::clamp(UV.Y, 0.0, 1.0);  // Flip V to image coordinates

        int i = static_cast<int>(u * m_Image.Width);
        int j = static_cast<int>(v * m_Image.Height);

        // Clamp integer mapping, since actual coordinates should be less than 1.0
        if (i >= m_Image.Width) { i = m_Image.Width - 1; }
        if (j >= m_Image.Height) { j = m_Image.Height - 1; }

        return m_Image.GetPixelAt(i, j);
    }
private:
    STBImage m_Image;
};
