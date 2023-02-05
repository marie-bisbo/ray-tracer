// RayTracingInOneWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "colour.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

Colour RayColour(const Ray& ray)
{
    Vec3 unitDirection = UnitVector(ray.Direction());
    auto t = 0.5f * (unitDirection.y() + 1.f);

    return (1.f - t) * Colour(1.f, 1.f, 1.f) + t * Colour(0.5f, 0.7f, 1.f);
}

int main()
{
    //Image

    const auto aspectRatio = 16.f / 9.f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    //Camera

    auto viewportHeight = 2.f;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.f;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewportWidth, 0, 0);
    auto vertical = Vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

    //Render 

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            auto u = double(i) / (imageWidth - 1);
            auto v = double(j) / (imageHeight - 1);
            Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            Colour pixelColour = RayColour(ray);

            WriteColour(std::cout, pixelColour);
        }
    }

    std::cerr << "\nDone.\n";
}

