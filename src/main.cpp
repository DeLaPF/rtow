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
    scene.addComponent(std::make_shared<Sphere>(Vec3(0, 0, 0), 0.5));
    scene.addComponent(std::make_shared<Sphere>(Vec3(0, -100.5, 0), 100));

    // Renderer
    Renderer renderer = Renderer();
    renderer.Resize(1280, 720);

    // Output
    renderer.Render(scene, camera);

    return 0;
}
