#pragma once

#include "Math/Vec3.h"

struct Image {
    Vec3* Data = nullptr;
    uint32_t Width = 0;
    uint32_t Height = 0;
    double AspectRatio = 0.0;
};

