// RayTracingInOneWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "colour.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

bool HitSphere(const Point3& centre, double radius, const Ray& ray)
{
    Vec3 originCentre = ray.Origin() - centre;
    auto a = Dot(ray.Direction(), ray.Direction());
    auto b = 2.f * Dot(originCentre, ray.Direction());
    auto c = Dot(originCentre, originCentre) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    return (discriminant > 0);
}

Colour RayColour(const Ray& ray)
{
    if (HitSphere(Point3(0, 0, -1), 0.5, ray))
    {
        return Colour(1, 0, 0);
    }
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

