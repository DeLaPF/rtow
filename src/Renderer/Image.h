#pragma once

#include "Math/Utils.h"
#include "Math/Vec.h"

struct Image {
    Vec3* Data = nullptr;
    uint32_t Width = 0;
    uint32_t Height = 0;
    double AspectRatio = 0.0;

    static inline void OutputImage(std::ostream &out, const Image& frame) {
        out << "P3\n" << frame.Width << ' ' << frame.Height << "\n255\n";
        for (uint32_t y = 0; y < frame.Height; y++) {
            for (uint32_t x = 0; x < frame.Width; x++) {
                const Vec3& color = frame.Data[(y * frame.Width) + x];
                // Write the translated [0,255] value of each color component.
                // Gamma Correct: color = (color)^(1/gamma) (we use gamma = 2.0)
                out << static_cast<int>(256 * Utils::clamp(std::sqrt(color.X), 0.0, 0.999)) << ' '
                    << static_cast<int>(256 * Utils::clamp(std::sqrt(color.Y), 0.0, 0.999)) << ' '
                    << static_cast<int>(256 * Utils::clamp(std::sqrt(color.Z), 0.0, 0.999)) << '\n';
            }
        }
    }
};

