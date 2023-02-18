#include "Camera/Camera.h"
#include "Math/Timer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Image.h"
#include "Scene/Scene.h"
#include "Scene/Sphere.h"
#include "Math/Utils.h"
#include "Math/Vec3.h"

#include <memory>

void WriteColor(std::ostream &out, Vec3 color) {
    // Write the translated [0,255] value of each color component.
    // Gamma Correct: color = (color)^(1/gamma) (we use gamma = 2.0)
    out << static_cast<int>(256 * Utils::clamp(std::sqrt(color.X), 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Utils::clamp(std::sqrt(color.Y), 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Utils::clamp(std::sqrt(color.Z), 0.0, 0.999)) << '\n';
}

void OutputImage(std::ostream &out, const Image& image) {
    out << "P3\n" << image.Width << ' ' << image.Height << "\n255\n";
    for (uint32_t y = 0; y < image.Height; y++) {
        for (uint32_t x = 0; x < image.Width; x++) {
            WriteColor(out, image.Data[(y * image.Width) + x]);
        }
    }
}

int main() {
    // Camera
    Camera camera = Camera();

    // Scene
    Scene scene = Scene();
    scene.addMaterial(std::make_shared<Material>(Material(Vec3(0.8, 0.8, 0.0), 1.0)));
    scene.addMaterial(std::make_shared<Material>(Material(Vec3(0.7, 0.3, 0.3), 1.0)));
    scene.addMaterial(std::make_shared<Material>(Material(Vec3(0.8, 0.8, 0.8), 0.3)));
    scene.addMaterial(std::make_shared<Material>(Material(Vec3(0.8, 0.6, 0.2), 0.7)));
    scene.addComponent(std::make_shared<Sphere>(Vec3(0, -100.5, 0), 100, 0));
    scene.addComponent(std::make_shared<Sphere>(Vec3(0, 0, 0), 0.5, 1));
    scene.addComponent(std::make_shared<Sphere>(Vec3(-1.0, 0, 0), 0.5, 2));
    scene.addComponent(std::make_shared<Sphere>(Vec3(1.0, 0, 0), 0.5, 3));

    // Renderer
    Renderer renderer = Renderer();
    renderer.Resize(1280, 720);

    // Render
    Timer timer;
    const Image& frame = renderer.Render(scene, camera);
    std::cerr << "\nGenerated in: " << timer.ElapsedSeconds() << "s\n";

    // Output
    OutputImage(std::cout, frame);
    std::cerr << "\nWritten in: " << timer.ElapsedSeconds() << "s\n";
    std::cerr << "\nDone.\n";

    return 0;
}
