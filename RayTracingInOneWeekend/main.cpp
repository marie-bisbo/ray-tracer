// RayTracingInOneWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "common.h"
#include "colour.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

double HitSphere(const Point3& centre, double radius, const Ray& ray)
{
    Vec3 originCentre = ray.Origin() - centre;
    auto a = ray.Direction().LengthSquared();
    auto halfB = Dot(originCentre, ray.Direction());
    auto c = originCentre.LengthSquared() - radius * radius;
    auto discriminant = halfB * halfB - a * c;

    return discriminant < 0.f ? -1.f : (-halfB - std::sqrt(discriminant)) / a;
}

Colour RayColour(const Ray& ray, const Hittable& world, int recursionDepth)
{
    HitRecord hitRecord;

    if (recursionDepth <= 0)
    {
        return Colour(0, 0, 0);
    }

    if (world.Hit(ray, 0.001, infinity, hitRecord))
    {
        Colour attenuation;
        Ray scattered;
        if (hitRecord.materialPtr->Scatter(ray, hitRecord, attenuation, scattered))
        {
            return attenuation * RayColour(scattered, world, recursionDepth - 1);
        }

        return Colour(0, 0, 0);
    }

    Vec3 unitDirection = UnitVector(ray.Direction());
    auto t = 0.5f * (unitDirection.y() + 1.f);

    return (1.f - t) * Colour(1.f, 1.f, 1.f) + t * Colour(0.5f, 0.7f, 1.f);
}

HittableList randomScene() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = GenerateRandomDoubleNormalised();
            Point3 center(a + 0.9 * GenerateRandomDoubleNormalised(), 0.2, b + 0.9 * GenerateRandomDoubleNormalised());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Colour::Random() * Colour::Random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Colour::Random(0.5, 1);
                    auto fuzz = GenerateRandomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}


int main()
{
    // Image

    const auto aspectRatio = 3.f / 2.f;
    const int imageWidth = 1200;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 1;
    const int maxRecursionDepth = 50;

    // World

    auto world = randomScene();

    // Camera

    Point3 lookFrom(13, 2, 3);
    Point3 lookAt(0, 0, 0);
    Vec3 verticalUp(0, 1, 0);
    auto distanceToFocus = 10.f;
    auto aperture = 0.1;

    Camera camera(lookFrom, lookAt, verticalUp, 20, aspectRatio, aperture, distanceToFocus);

    // Render 

    int counter = 0;
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            Colour pixelColour(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                counter++;
				std::cerr << "\rSamples count: " << counter << ' ' << std::flush;
				auto u = (i + GenerateRandomDoubleNormalised()) / (imageWidth - 1);
				auto v = (j + GenerateRandomDoubleNormalised()) / (imageHeight - 1);
                Ray ray = camera.GetRay(u, v);
                pixelColour += RayColour(ray, world, maxRecursionDepth);
            }

            WriteColour(std::cout, pixelColour, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}

