#include "Camera/Camera.h"
#include "Math/Timer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Image.h"
#include "Scene/Scene.h"
#include "Scene/Sphere.h"
#include "Math/Utils.h"
#include "Math/Vec3.h"

#include <cstdint>
#include <fstream>
#include <memory>
#include <string>

void OutputFrame(std::ostream &out, const Image& frame) {
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

int main(int argc, char* argv[]) {
    // Scene
    Scene scene = Scene();
    scene.addMaterial(std::make_shared<Material>(Material(Vec3(0.8, 0.8, 0.0), 0.5)));
    scene.addMaterial(std::make_shared<Material>(Material(Vec3(0.7, 0.3, 0.3), 0.5)));
    scene.addMaterial(std::make_shared<Material>(Material(Vec3(1.0, 1.0, 1.0), 0.0, 0.0, 1.5)));
    scene.addMaterial(std::make_shared<Material>(Material(Vec3(0.8, 0.6, 0.2), 0.4)));
    scene.addComponent(std::make_shared<Sphere>(Vec3(0, -100.5, 0), 100, 0));
    scene.addComponent(std::make_shared<Sphere>(Vec3(0, 0, 0), 0.5, 1));
    scene.addComponent(std::make_shared<Sphere>(Vec3(-1.0, 0, 0), 0.5, 2));
    scene.addComponent(std::make_shared<Sphere>(Vec3(-1.0, 0, 0), -0.4, 2));
    scene.addComponent(std::make_shared<Sphere>(Vec3(1.0, 0, 0), 0.5, 3));

    // Image
    uint32_t imageWidth = 1280, imageHeight = 720;

    // Camera
    Camera camera = Camera();
    camera.SetFOV(90);
    camera.SetAperture(0.5);
    camera.Resize(imageWidth, imageHeight);
    camera.SetView(Vec3(-2, 2, 1), Vec3(0, 0, 0));

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
    OutputFrame(file, frame);
    file.close();

    std::cerr << "\nWritten in: " << timer.ElapsedSeconds() << "s\n";
    std::cerr << "\nDone.\n";

    return 0;
}
