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

int main()
{
    // Image

    const auto aspectRatio = 16.f / 9.f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxRecursionDepth = 50;

    // World
    HittableList worldObjects;

    auto materialGround = std::make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
    auto materialCentre = std::make_shared<Lambertian>(Colour(0.7, 0.3, 0.3));
    auto materialLeft = std::make_shared<Metal>(Colour(0.8, 0.8, 0.8), 0.3);
    auto materialRight = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2), 1.0);

    worldObjects.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
    worldObjects.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, materialCentre));
    worldObjects.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    worldObjects.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

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
                pixelColour += RayColour(ray, worldObjects, maxRecursionDepth);
            }

            WriteColour(std::cout, pixelColour, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}

