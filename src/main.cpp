#include "Camera/Camera.h"
#include "Math/Random.h"
#include "Math/Timer.h"
#include "Math/Vec3.h"
#include "Renderer/Renderer.h"
#include "Renderer/Image.h"
#include "Scene/Scene.h"
#include "Scene/Sphere.h"

#include <fstream>
#include <iostream>
#include <memory>

Scene GenRandomScene();
int main(int argc, char* argv[]) {
    // Scene
    Scene scene = GenRandomScene();

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

Scene GenRandomScene() {
    Scene scene;

    //Material() : Albedo(Vec3()), Roughness(0.5), Metallic(1.0), IndexOfRefraction(1.0)
    scene.addMaterial(std::make_shared<Material>(Vec3(0.5, 0.5, 0.5)));
    scene.addMaterial(std::make_shared<Material>(Vec3(1, 1, 1), 0, 0, 1.5));
    scene.addMaterial(std::make_shared<Material>(Vec3(0.4, 0.2, 0.1), 1, 1, 0));
    scene.addMaterial(std::make_shared<Material>(Vec3(0.7, 0.6, 0.5), 0, 1, 0));

    scene.addComponent(std::make_shared<Sphere>(Vec3(0,-1000,0), 1000, 0));
    scene.addComponent(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, 1));
    scene.addComponent(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, 2));
    scene.addComponent(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, 3));

    int matInd = 4;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double chooseMat = Random::Double();
            Vec3 center(a + 0.9 * Random::Double(), 0.2, b + 0.9 * Random::Double());
            if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphereMat;

                if (chooseMat < 0.8) {
                    // diffuse
                    auto albedo = Vec3::random() * Vec3::random();
                    sphereMat = std::make_shared<Material>(albedo);
                    scene.addComponent(std::make_shared<Sphere>(center, 0.2, matInd));
                } else if (chooseMat < 0.95) {
                    // metal
                    auto albedo = Vec3::random(0.5, 1);
                    auto fuzz = Random::Double(0, 0.5);
                    sphereMat = std::make_shared<Material>(albedo, fuzz);
                    scene.addComponent(std::make_shared<Sphere>(center, 0.2, matInd));
                } else {
                    // glass
                    sphereMat = std::make_shared<Material>(Vec3(1, 1, 1), 0, 0, 1.5);
                    scene.addComponent(std::make_shared<Sphere>(center, 0.2, matInd));
                }
                scene.addMaterial(sphereMat);
                matInd++;
            }
        }
    }

    return scene;
}
