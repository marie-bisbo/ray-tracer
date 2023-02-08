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

Colour RayColour(const Ray& ray, const Hittable& world)
{
    HitRecord hitRecord;
    if (world.Hit(ray, 0, infinity, hitRecord))
    {
        return 0.5f * (hitRecord.normal + Colour(1, 1, 1));
    }

    Vec3 unitDirection = UnitVector(ray.Direction());
    auto t = 0.5f * (unitDirection.y() + 1.f);

    return (1.f - t) * Colour(1.f, 1.f, 1.f) + t * Colour(0.5f, 0.7f, 1.f);
}

int main()
{
    // Image

    const auto aspectRatio = 16.f / 9.f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;

    // World
    HittableList worldObjects;
    worldObjects.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5f));
    worldObjects.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera

    Camera camera;

    // Render 

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            Colour pixelColour(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
				auto u = (i + GenerateRandomDoubleNormalised()) / (imageWidth - 1);
				auto v = (j + GenerateRandomDoubleNormalised()) / (imageHeight - 1);
                Ray ray = camera.GetRay(u, v);
                pixelColour += RayColour(ray, worldObjects);
            }

            WriteColour(std::cout, pixelColour, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}

