#pragma once

#include "Math/Ray.h"
#include "Math/Vec3.h"

class Camera {
    public:
        Camera() : Origin(Vec3(0, 0, 1)), FocalLength(1.0) {}

    public:
        Vec3 Origin;
        double FocalLength;
};
