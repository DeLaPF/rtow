#include "Scene.h"

void Scene::addComponent(std::shared_ptr<SceneComponent> component) {
    if (auto traceableComponent = std::dynamic_pointer_cast<TraceableComponent>(component)) {
        m_TraceableComponents.push_back(traceableComponent);
    } else {
        m_SceneComponents.push_back(component);
    }
}

std::shared_ptr<SceneComponent> Scene::GetComponentAt(int index) const {
    if (index < 0 || index >= m_SceneComponents.size()) {
        return std::make_shared<SceneComponent>(SceneComponent());
    }

    return m_SceneComponents.at(index);
}

std::shared_ptr<TraceableComponent> Scene::GetTraceableComponentAt(int index) const {
    if (index < 0 || index >= m_TraceableComponents.size()) {
        return std::make_shared<TraceableComponent>(TraceableComponent());
    }

    return m_TraceableComponents.at(index);
}

std::shared_ptr<Material> Scene::GetMaterial(int index) const {
    if (index < 0 || index >= m_Materials.size()) {
        return std::make_shared<Material>(Material());
    }

    return m_Materials.at(index);
}

bool Scene::RayCast(const Ray& ray, double distMin, double distMax, TraceResult& res) const {
    double nearestHit = distMax;
    for (size_t i = 0; i < m_TraceableComponents.size(); i++) {
        if (m_TraceableComponents.at(i)->Trace(ray, distMin, nearestHit, res)) {
            nearestHit = res.HitDistance;
            res.HitIndex = (int)i;
        }
    }
    return res.Success;
}
void Scene::GenBoundingVolumeHierarchy() {
    m_TraceableComponents.push_back(std::make_shared<BVHNode>(m_TraceableComponents, 0, m_TraceableComponents.size()));
}
Scene Scene::GenRandomScene() {
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
