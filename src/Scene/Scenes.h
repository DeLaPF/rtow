#pragma once

#include "Scene.h"
#include "Camera/Camera.h"

namespace Scenes {
    static void MaterialTest(Scene& scene, Camera& camera) {
        scene.addMaterial(std::make_shared<Material>(Vec3(0.5, 0.5, 0.5)));
        scene.addMaterial(std::make_shared<Material>(Vec3(0.4, 0.2, 0.1), 1, 1, 0));
        scene.addMaterial(std::make_shared<Material>(Vec3(0.7, 0.6, 0.5), 0, 1, 0));
        scene.addMaterial(std::make_shared<Material>(Vec3(1, 1, 1), 0, 0, 1.5));
        scene.addMaterial(std::make_shared<Material>(Vec3(0.6, 0.8, 1), 0.5, 0.2, 1.5));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0,-1000,0), 1000, 0));
        scene.addComponent(std::make_shared<Sphere>(Vec3(-2.25, 1, 0), 1.0, 1));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, 2));
        scene.addComponent(std::make_shared<Sphere>(Vec3(2.25, 1, 0), 1.0, 3));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0, 3.25, 0), 1.0, 4));

        camera.SetView(Vec3(0, 2, 5.5), Vec3(0, 2, 0));
        camera.SetFocalLength(2.0);
    }

    static void CheckeredSpheres(Scene& scene, Camera& camera) {
        std::shared_ptr<Texture> checkered = std::make_shared<CheckeredTexture>(Vec3(0.2, 0.3, 0.1), Vec3(0.9, 0.9, 0.9));
        scene.addMaterial(std::make_shared<Material>(checkered));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0,-10, 0), 10, 0));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0, 10, 0), 10, 0));

        camera.SetFOV(20);
        camera.SetAperture(0.1);
        camera.SetView(Vec3(13, 2, 3), Vec3(0, 0, 0));
        camera.SetFocusDist(10);
    }

    static void RandomSpheres(Scene& scene, Camera& camera) {
        scene.addMaterial(std::make_shared<Material>(Vec3(0.5, 0.5, 0.5)));
        scene.addMaterial(std::make_shared<Material>(Vec3(1, 1, 1), 0, 0, 1.5));
        scene.addMaterial(std::make_shared<Material>(Vec3(0.4, 0.2, 0.1), 1, 1, 0));
        scene.addMaterial(std::make_shared<Material>(Vec3(0.7, 0.6, 0.5), 0, 1, 0));


        std::vector<std::shared_ptr<TraceableComponent>> traceableComponents;
        traceableComponents.push_back(std::make_shared<Sphere>(Vec3(0,-1000,0), 1000, 0));
        traceableComponents.push_back(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, 1));
        traceableComponents.push_back(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, 2));
        traceableComponents.push_back(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, 3));

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
                        traceableComponents.push_back(std::make_shared<Sphere>(center, 0.2, matInd));
                    } else if (chooseMat < 0.95) {
                        // metal
                        auto albedo = Vec3::random(0.5, 1);
                        auto fuzz = Random::Double(0, 0.5);
                        sphereMat = std::make_shared<Material>(albedo, fuzz);
                        traceableComponents.push_back(std::make_shared<Sphere>(center, 0.2, matInd));
                    } else {
                        // glass
                        sphereMat = std::make_shared<Material>(Vec3(1, 1, 1), 0, 0, 1.5);
                        traceableComponents.push_back(std::make_shared<Sphere>(center, 0.2, matInd));
                    }
                    scene.addMaterial(sphereMat);
                    matInd++;
                }
            }
        }
        scene.addComponent(std::make_shared<BVHNode>(traceableComponents, 0, traceableComponents.size()));

        camera.SetFOV(20);
        camera.SetAperture(0.1);
        camera.SetView(Vec3(13, 2, 3), Vec3(0, 0, 0));
        camera.SetFocusDist(10);
    }
}
