#pragma once

#include "vec3.h"

class Ray 
{
public:
	Ray() {}
	Ray(const Point3& origin, const Vec3& direction)
		: m_Origin(origin), m_Direction(direction)
	{}

	Point3 Origin() const { return m_Origin; }
	Vec3 Direction() const { return m_Direction; }

	Point3 At(double scalar) const { return m_Origin + scalar * m_Direction; }

public:
	Point3 m_Origin;
	Vec3 m_Direction;
};
