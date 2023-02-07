#pragma once

#include "vec3.h"
#include "ray.h"

struct HitRecord
{
	Point3 point;
	Vec3 normal;
	double t;
};

class Hittable
{
public:
	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const = 0;
};
