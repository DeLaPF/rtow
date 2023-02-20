#pragma once

#include "Material.h"
#include "SceneComponent.h"
#include "Sphere.h"

#include <memory>
#include <vector>

class Scene {
    public:
        Scene() {}

        void addComponent(std::shared_ptr<SceneComponent> component) { m_Components.push_back(component); }
        void clearComponents() { m_Components.clear(); }
        std::shared_ptr<SceneComponent> GetComponent(int index) const;

        void addMaterial(std::shared_ptr<Material> material) { m_Materials.push_back(material); }
        void clearMaterials() { m_Materials.clear(); }
        std::shared_ptr<Material> GetMaterial(int index) const;

        HitResult RayCast(const Ray& ray, double distMin, double distMax) const;
    public:
        std::vector<std::shared_ptr<SceneComponent>> m_Components;
        std::vector<std::shared_ptr<Material>> m_Materials;
    public:
        static Scene GenRandomScene() {
            Scene scene;
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
};
