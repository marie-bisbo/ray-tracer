#pragma once

#include "common.h"
#include "ray.h"
#include "vec3.h"

struct HitRecord;

class Material
{
public:
	virtual bool Scatter(
		const Ray& rayIn,
		const HitRecord& hitRecord,
		Colour& attenuation,
		Ray& scattered
	) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const Colour& albedo)
		: m_Albedo(albedo) {}

	virtual bool Scatter(
		const Ray& rayIn,
		const HitRecord& hitRecord,
		Colour& attenuation,
		Ray& scattered
	) const override
	{
		auto scatterDirection = hitRecord.normal + RandomUnitVector();
		if (scatterDirection.NearlyZero())
		{
			scatterDirection = hitRecord.normal;
		}

		attenuation = m_Albedo;
		scattered = Ray(hitRecord.point, scatterDirection);
		return true;
	}

public:
	Colour m_Albedo;
};

class Metal : public Material
{
public:
	Metal(const Colour& albedo)
		: m_Albedo(albedo) {}

	virtual bool Scatter(
		const Ray& rayIn,
		const HitRecord& hitRecord,
		Colour& attenuation,
		Ray& scattered
	) const override
	{
		Vec3 reflected = Reflect(UnitVector(rayIn.Direction()), hitRecord.normal);
		attenuation = m_Albedo;
		scattered = Ray(hitRecord.point, reflected);

		return Dot(scattered.Direction(), hitRecord.normal) > 0;
	}

public:
	Colour m_Albedo;
};

