#include "Material/STBImage.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION // use stb functions once and for all
#include "libs/stb_image.h"

STBImage::~STBImage() { 
    if (Data) { stbi_image_free(Data); }
}

void STBImage::LoadImage(const char* filename) {
    if (Data) { stbi_image_free(Data); }

    int compPerPixel = BytesPerPixel;
    Data = stbi_load(filename, &Width, &Height, &compPerPixel, compPerPixel);
    if (!Data) {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        Width = Height = 0;
    }

    BytesPerScanline = BytesPerPixel * Width;
}

Vec3 STBImage::GetPixelAt(int i, int j) const {
    unsigned char* pixel = Data + (j * BytesPerScanline) + (i * BytesPerPixel);
    return Vec3(pixel[0], pixel[1], pixel[2]) / 255.0;
}
