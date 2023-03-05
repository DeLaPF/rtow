#pragma once

#include "Math/Vec.h"

class STBImage {
public:
    STBImage() : Data(nullptr), Width(0), Height(0), BytesPerScanline(0) {}
    STBImage(const char* filename) : STBImage() { LoadImage(filename); }
    ~STBImage();

    void LoadImage(const char* filename);

    Vec3 GetPixelAt(int i, int j) const;
public:
    unsigned char* Data;
    int Width;
    int Height;
    int BytesPerScanline;

    const static int BytesPerPixel = 3;
};
