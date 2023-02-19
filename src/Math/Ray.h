#pragma once

#include "Vec3.h"

class Ray {
    public:
        Ray() {}
        Ray(Vec3 origin, Vec3 direction) : Origin(origin), Direction(direction) {}

        Vec3 At(double t) const { return Origin + (t * Direction); }

    public:
        Vec3 Origin;
        Vec3 Direction;
};
