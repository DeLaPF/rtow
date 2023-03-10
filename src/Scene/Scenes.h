#pragma once

#include "Camera/Camera.h"
#include "Material/Texture.h"
#include "Renderer/Renderer.h"
#include "Scene/AxisAlignedBox.h"
#include "Scene/AxisAlignedRect.h"
#include "Scene/Scene.h"
#include "Scene/Sphere.h"

namespace Scenes {
    static void CheckeredSpheres(Scene& scene, Camera& camera, Renderer& renderer) {
        std::shared_ptr<Texture> checkered = std::make_shared<CheckeredTexture>(Vec3(0.2, 0.3, 0.1), Vec3(0.9, 0.9, 0.9));
        scene.addMaterial(std::make_shared<Material>(checkered));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0,-10, 0), 10, 0));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0, 10, 0), 10, 0));

        camera.SetFOV(20);
        camera.SetAperture(0.1);
        camera.SetView(Vec3(13, 2, 3), Vec3(0, 0, 0));
        camera.SetFocusDist(10);

        renderer.SetBackgroundColor(Vec3(0.5, 0.7, 1.0));
    }

    static void CornellBox(Scene& scene, Camera& camera, Renderer& renderer) {
        scene.addMaterial(std::make_shared<Material>(Vec3(.65, .05, .05)));
        scene.addMaterial(std::make_shared<Material>(Vec3(.73, .73, .73)));
        scene.addMaterial(std::make_shared<Material>(Vec3(.12, .45, .15)));
        scene.addMaterial(std::make_shared<Material>(Vec3(), Vec3(15)));

        scene.addComponent(std::make_shared<RectYZ>(Vec3(0, 0, 0), Vec2(555), 0));
        scene.addComponent(std::make_shared<RectYZ>(Vec3(555, 0, 0), Vec2(555), 2));
        scene.addComponent(std::make_shared<RectXZ>(Vec3(213, 554, 227), Vec2(130, 105), 3));
        scene.addComponent(std::make_shared<RectXZ>(Vec3(0, 0, 0), Vec2(555), 1));
        scene.addComponent(std::make_shared<RectXZ>(Vec3(0, 555, 0), Vec2(555), 1));
        scene.addComponent(std::make_shared<RectXY>(Vec3(0, 0, 555), Vec2(555), 1));
        scene.addComponent(std::make_shared<Box>(Vec3(130, 0, 65), Vec3(165, 165, 165), Vec3(0, -18, 0), 1));
        scene.addComponent(std::make_shared<Box>(Vec3(265, 0, 295), Vec3(165, 330, 165), Vec3(0, 15, 0), 1));
        scene.GenBoundingVolumeHierarchy();

        camera.SetFOV(40);
        camera.SetView(Vec3(278, 278, -800), Vec3(278, 278, 0));

        renderer.SetBackgroundColor(Vec3());
        renderer.SetSamplesPerPixel(200);
    }

    static void Earth(Scene& scene, Camera& camera, Renderer& renderer) {
        std::shared_ptr<Texture> earthTexture = std::make_shared<ImageTexture>("external/textures/earthmap.jpg");
        scene.addMaterial(std::make_shared<Material>(earthTexture));
        scene.addComponent(std::make_shared<Sphere>(Vec3(), 2, 0));

        camera.SetFOV(20);
        camera.SetAperture(0.1);
        camera.SetView(Vec3(13, 2, 3), Vec3(0, 0, 0));

        renderer.SetBackgroundColor(Vec3(0.5, 0.7, 1.0));
    }

    static void EmissiveRectangleTest(Scene& scene, Camera& camera, Renderer& renderer) {
        std::shared_ptr<Texture> marble = std::make_shared<MarbleTexture>(2);
        scene.addMaterial(std::make_shared<Material>(marble));
        scene.addMaterial(std::make_shared<Material>(Vec3(0.5), Vec3(5, 2, 2)));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0,-1000,0), 1000, 0));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0, 2, 0), 2, 0));
        scene.addComponent(std::make_shared<RectXY>(Vec3(3, 1, -2), Vec2(2), 1));

        camera.SetFOV(20);
        camera.SetView(Vec3(26, 3, 6), Vec3(0, 2, 0));

        renderer.SetBackgroundColor(Vec3());
    }

    static void EmissiveSphereTest(Scene& scene, Camera& camera, Renderer& renderer) {
        std::shared_ptr<Texture> marble = std::make_shared<MarbleTexture>(2);
        scene.addMaterial(std::make_shared<Material>(marble));
        scene.addMaterial(std::make_shared<Material>(Vec3(0.5), Vec3(5, 2, 2)));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0,-1000,0), 1000, 0));
        scene.addComponent(std::make_shared<Sphere>(Vec3(0, 1, 0), 1, 0));
        scene.addComponent(std::make_shared<Sphere>(Vec3(2, 4, -2), 2, 1));

        camera.SetFOV(30);
        camera.SetAperture(0.1);
        camera.SetView(Vec3(13, 2, 3), Vec3(0, 0, 0));

        renderer.SetBackgroundColor(Vec3());
    }

    static void MaterialTest(Scene& scene, Camera& camera, Renderer& renderer) {
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

        renderer.SetBackgroundColor(Vec3(0.5, 0.7, 1.0));
    }

    static void PerlinSpheres(Scene& scene, Camera& camera, Renderer& renderer) {
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

        renderer.SetBackgroundColor(Vec3(0.5, 0.7, 1.0));
    }

    static void RandomSpheres(Scene& scene, Camera& camera, Renderer& renderer) {
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

        renderer.SetBackgroundColor(Vec3(0.5, 0.7, 1.0));
    }

    static void TransformTest(Scene& scene, Camera& camera, Renderer& renderer) {
        std::shared_ptr<Texture> earthTexture = std::make_shared<ImageTexture>("external/textures/earthmap.jpg");
        scene.addMaterial(std::make_shared<Material>(earthTexture));
        scene.addMaterial(std::make_shared<Material>(Vec3(.65, .05, .05)));
        scene.addMaterial(std::make_shared<Material>(Vec3(.73, .73, .73)));
        scene.addMaterial(std::make_shared<Material>(Vec3(.12, .45, .15)));
        scene.addMaterial(std::make_shared<Material>(Vec3(), Vec3(15)));

        scene.addComponent(std::make_shared<RectYZ>(Vec3(2.5, 0, 0), Vec2(5), Vec3(0, -45, 0), 3));
        scene.addComponent(std::make_shared<RectXY>(Vec3(2.5, 0, 0), Vec2(5), Vec3(0, -45, 0), 1));
        scene.addComponent(std::make_shared<RectXZ>(Vec3(-1.035, 0, 3.535), Vec2(5), Vec3(0, 45, 0), 2));
        scene.addComponent(std::make_shared<RectXZ>(Vec3(-1.035, 5, 3.535), Vec2(5), Vec3(0, 45, 0), 2));
        scene.addComponent(std::make_shared<RectXZ>(Vec3(1.793, 4.999, 3.535), Vec2(1), Vec3(0, 45, 0), 4));
        scene.addComponent(std::make_shared<Sphere>(Vec3(2.5, 2.5, 3.535), 1.5, Vec3(-45, 143, -22), 0));
        scene.GenBoundingVolumeHierarchy();

        camera.SetView(Vec3(2.5, 2, 15), Vec3(2.5, 2.75, 0));
        camera.SetFocalLength(3);

        renderer.SetBackgroundColor(Vec3(0.5, 0.7, 1.0));
    }
}
