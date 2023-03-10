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
	Metal(const Colour& albedo, double fuzziness)
		: m_Albedo(albedo), m_Fuziness(fuzziness) {}

	virtual bool Scatter(
		const Ray& rayIn,
		const HitRecord& hitRecord,
		Colour& attenuation,
		Ray& scattered
	) const override
	{
		Vec3 reflected = Reflect(UnitVector(rayIn.Direction()), hitRecord.normal);
		attenuation = m_Albedo;
		scattered = Ray(hitRecord.point, reflected + m_Fuziness * RandomPointInUnitSphere());

		return Dot(scattered.Direction(), hitRecord.normal) > 0;
	}

public:
	Colour m_Albedo;
	double m_Fuziness;
};

class Dielectric : public Material
{
public:
	Dielectric(double indexOfRefraction)
		: m_IndexOfRefraction(indexOfRefraction) {}

	virtual bool Scatter(
		const Ray& rayIn,
		const HitRecord& hitRecord,
		Colour& attenuation,
		Ray& scattered
	) const override
	{
		attenuation = Colour(1.0, 1.0, 1.0);
		double refractionRatio = hitRecord.frontFace ? (1.0 / m_IndexOfRefraction) : m_IndexOfRefraction;

		Vec3 unitDirection = UnitVector(rayIn.Direction());
		double cosTheta = fmin(Dot(-unitDirection, hitRecord.normal), 1.0);
		double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

		bool cannotRefract = refractionRatio * sinTheta > 1.0;

		Vec3 direction;
		if (cannotRefract || CalculateReflectance(cosTheta, refractionRatio) > GenerateRandomDoubleNormalised())
		{
			direction = Reflect(unitDirection, hitRecord.normal);
		}
		else
		{
			direction = Refract(unitDirection, hitRecord.normal, refractionRatio);
		}

		scattered = Ray(hitRecord.point, direction);

		return true;
	}

public:
	double m_IndexOfRefraction;

private:
	static double CalculateReflectance(double cosine, double refractionIndex)
	{
		// Schlick's approximation for reflectance
		auto rZero = (1 - refractionIndex) / (1 + refractionIndex);
		rZero = rZero * rZero;

		return rZero + (1 - rZero) * pow((1 - cosine), 5);
	}
};

