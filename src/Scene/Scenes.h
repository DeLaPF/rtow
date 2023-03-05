#pragma once

#include "Camera/Camera.h"
#include "Material/Texture.h"
#include "Scene/Scene.h"
#include "Scene/Sphere.h"

namespace Scenes {
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

    static void Earth(Scene& scene, Camera& camera) {
        std::shared_ptr<Texture> eartTexture = std::make_shared<ImageTexture>("external/textures/earthmap.jpg");
        scene.addMaterial(std::make_shared<Material>(eartTexture));
        scene.addComponent(std::make_shared<Sphere>(Vec3(), 2, 0));

        camera.SetFOV(20);
        camera.SetAperture(0.1);
        camera.SetView(Vec3(13, 2, 3), Vec3(0, 0, 0));
    }

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
        scene.GenBoundingVolumeHierarchy();

        camera.SetView(Vec3(0, 2, 5.5), Vec3(0, 2, 0));
        camera.SetFocalLength(2.0);
    }

    static void PerlinSpheres(Scene& scene, Camera& camera) {
        std::shared_ptr<Texture> perlinNoise = std::make_shared<PerlinNoiseTexture>(4);
        std::shared_ptr<Texture> perlinTurbulence = std::make_shared<PerlinTurbulenceTexture>(4, 7);
        std::shared_ptr<Texture> marble = std::make_shared<MarbleTexture>(4);
        scene.addMaterial(std::make_shared<Material>(perlinNoise));
        scene.addMaterial(std::make_shared<Material>(perlinTurbulence));
        scene.addMaterial(std::make_shared<Material>(marble));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0, -1000, 0), 1000, 0));
        scene.addComponent(std::make_shared<Sphere>(Vec3(-1.25, 1, 0), 1, 1));
        scene.addComponent(std::make_shared<Sphere>(Vec3(1.25, 1, 0), 1, 2));

        camera.SetView(Vec3(0, 2, 8), Vec3(0, 1, 0));
        camera.SetFocalLength(5);
    }

    static void RandomSpheres(Scene& scene, Camera& camera) {
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
        scene.GenBoundingVolumeHierarchy();

        camera.SetFOV(20);
        camera.SetAperture(0.1);
        camera.SetView(Vec3(13, 2, 3), Vec3(0, 0, 0));
        camera.SetFocusDist(10);
    }
}
