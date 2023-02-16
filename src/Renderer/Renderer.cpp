#include "Renderer.h"

#include "Math/Random.h"
#include "Math/Timer.h"
#include "Math/Utils.h"
#include "Scene/SceneComponent.h"

#include <thread>

namespace ImageUtils {
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
                ImageUtils::WriteColor(out, image.Data[(y * image.Width) + x]);
            }
        }
    }
}

void Renderer::Resize(uint32_t width, uint32_t height) {
    if (m_Image.Width == width && m_Image.Height == height) {
        return;
    }

    delete[] m_Image.Data;
    m_Image.Data = new Vec3[width * height];
    m_Image.Width = width;
    m_Image.Height = height;
    m_Image.AspectRatio = (double)width / height;
}

void Renderer::Render(const Scene &scene, const Camera &camera) {
    Timer timer;
    m_ActiveScene = &scene;
    m_ActiveCamera = &camera;

    std::vector<std::thread> threads;
    for (uint32_t y = 0; y < m_Image.Height; y++) {
        threads.push_back(std::thread([this, y]() -> void {
            for (uint32_t x = 0; x < m_Image.Width; x++) {
                Vec3 color = Vec3();
                for (uint32_t i = 0; i < m_Samples; i++) {
                    // u: -1 to aspectRatio (left to right), v: -1 to 1 (top to bottom)
                    double u = (2.0 * ((x + RandomDouble()) / (m_Image.Width - 1.0)) - 1.0) * m_Image.AspectRatio;
                    double v = 2.0 * ((m_Image.Height - y + RandomDouble()) / m_Image.Height) - 1.0;
                    //color += RayGen(u, v) / m_Samples;
                    Ray ray = Ray(m_ActiveCamera->Origin, Vec3(u, v, -m_ActiveCamera->FocalLength));
                    color += RTOWColor(ray, 0) / m_Samples;
                }
                m_Image.Data[(y * m_Image.Width) + x] = color;
            }
        }));
    }
    for (auto& thread : threads) {
        thread.join();
    }

    std::cerr << "\nGenerated in: " << timer.ElapsedSeconds() << "s\n";
    ImageUtils::OutputImage(std::cout, m_Image);
    std::cerr << "\nWritten in: " << timer.ElapsedSeconds() << "s\n";
    std::cerr << "\nDone.\n";
}

Vec3 Renderer::RayGen(double u, double v) {
    Vec3 color = Vec3();
    double multiplier = 1.0;
    Ray ray = Ray(m_ActiveCamera->Origin, Vec3(u, v, -m_ActiveCamera->FocalLength));
    for (uint32_t i = 0; i < m_Bounces; i++) {
        HitResult res = m_ActiveScene->RayCast(ray, 0.0001, std::numeric_limits<double>::infinity());
        if (!res.DidHit) { // Miss
            Vec3 direction = Vec3Util::normalize(ray.Direction);
            double t = 0.5 * (direction.Y + 1.0);
            color += (((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0))) * multiplier; //Lerp
            break;
        }

        color += res.WorldNormal * multiplier;
        ray = Ray(res.WorldLocation, res.WorldNormal + Vec3Util::random(-0.5, 0.5));
        multiplier *= 0.5;
    }

    return color;
}

Vec3 Renderer::RTOWColor(const Ray& ray, uint32_t bounces) {
    if (bounces >= m_Bounces) {
        return Vec3();
    }

    HitResult res = m_ActiveScene->RayCast(ray, 0.0001, std::numeric_limits<double>::infinity());
    if (!res.DidHit) { // Miss
        Vec3 direction = Vec3Util::normalize(ray.Direction);
        double t = 0.5 * (direction.Y + 1.0);
        return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0)); //Lerp
    }

    return 0.5 * RTOWColor(Ray(res.WorldLocation, res.WorldNormal + Vec3Util::random(-0.5, 0.5)), ++bounces);
}
