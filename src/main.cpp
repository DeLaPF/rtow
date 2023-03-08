#include <fstream>
#include <iostream>

#include "Camera/Camera.h"
#include "Math/Timer.h"
#include "Renderer/Image.h"
#include "Renderer/Renderer.h"
#include "Scene/Scene.h"
#include "Scene/Scenes.h"

int main(int argc, char* argv[]) {
    // Setup
    Scene scene = Scene();
    Camera camera = Camera();
    Renderer renderer = Renderer();
    Scenes::TransformTest(scene, camera, renderer);

    // Render
    Timer timer;
    uint32_t imageWidth = 1280, imageHeight = 720;
    renderer.Resize(imageWidth, imageHeight);
    camera.Resize(imageWidth, imageHeight);
    const Image& frame = renderer.Render(scene, camera);
    std::cerr << "\nGenerated in: " << timer.ElapsedSeconds() << "s\n";

    // Output
    std::string fileName = "image.ppm";
    if (argc > 1) { fileName = argv[1]; }
    std::ofstream file;
    file.open(fileName);
    Image::OutputImage(file, frame);
    file.close();
    std::cerr << "\nWritten in: " << timer.ElapsedSeconds() << "s\n";
    std::cerr << "\nDone.\n";

    return 0;
}
