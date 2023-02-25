#pragma once

#include "common.h"
#include "vec3.h"
#include "ray.h"

class Material;

struct HitRecord
{
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> materialPtr;
	double t;
	bool frontFace;

	inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
	{
		frontFace = Dot(ray.Direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable
{
public:
	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const = 0;
};
