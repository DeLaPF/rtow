#include "Camera/Camera.h"
#include "Math/Timer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Image.h"
#include "Scene/Scene.h"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    // Scene
    Scene scene = Scene::GenRandomScene();
    scene.GenBoundingVolumeHierarchy();

    // Image
    uint32_t imageWidth = 1280, imageHeight = 720;

    // Camera
    Camera camera = Camera();
    camera.SetFOV(20);
    camera.SetAperture(0.1);
    camera.Resize(imageWidth, imageHeight);
    camera.SetView(Vec3(13, 2, 3), Vec3(0, 0, 0));
    camera.SetFocusDist(10);

    // Renderer
    Renderer renderer = Renderer();
    renderer.Resize(imageWidth, imageHeight);

    // Render
    Timer timer;
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
