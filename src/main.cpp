#include "Camera/Camera.h"
#include "Renderer/Renderer.h"
#include "Scene/Scene.h"
#include "Scene/Sphere.h"
#include "Math/Vec3.h"

#include <memory>

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

    // Output
    renderer.Render(scene, camera);

    return 0;
}
