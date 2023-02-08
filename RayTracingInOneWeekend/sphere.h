#pragma once

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable
{
public:
	Sphere() {}
	Sphere(Point3 centre, double radius)
		: m_Centre(centre), m_Radius(radius) {};

	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const override;

public:
	Point3 m_Centre;
	double m_Radius;
};

bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const
{
	Vec3 originCentre = ray.Origin() - m_Centre;
	auto a = ray.Direction().LengthSquared();
	auto halfB = Dot(originCentre, ray.Direction());
	auto c = originCentre.LengthSquared() - m_Radius * m_Radius;

	auto discriminant = halfB * halfB - a * c;

	if (discriminant < 0) return false;

	auto discriminantSquareRoot = std::sqrt(discriminant);
	auto root = (-halfB - discriminantSquareRoot) / a;
	if (root < tMin || tMax < root)
	{
		root = (-halfB + discriminantSquareRoot) / a;
		if (root < tMin || tMax < root)
		{
			return false;
		}
	}

	hitRecord.t = root;
	hitRecord.point = ray.At(hitRecord.t);
	hitRecord.normal = (hitRecord.point - m_Centre) / m_Radius;
	Vec3 outwardNormal = (hitRecord.point - m_Centre) / m_Radius;
	hitRecord.SetFaceNormal(ray, outwardNormal);

	return true;
}
