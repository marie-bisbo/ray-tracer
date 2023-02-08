#pragma once

#include "vec3.h"
#include "ray.h"

class Camera
{
public:
	Camera()
	{
		auto aspectRatio = 16.f / 9.f;
		auto viewportHeight = 2.f;
		auto viewportWidth = aspectRatio * viewportHeight;
		auto focalLength = 1.f;

		m_Origin = Point3(0, 0, 0);
		m_Horizontal = Vec3(viewportWidth, 0.f, 0.f);
		m_Vertical = Vec3(0.f, viewportHeight, 0.f);
		m_LowerLeftCorner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - Vec3(0, 0, focalLength);
	}

	Ray GetRay(const double u, const double v) const
	{
		return Ray(m_Origin, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical - m_Origin);
	}

private:
	Point3 m_Origin;
	Point3 m_LowerLeftCorner;
	Vec3 m_Horizontal;
	Vec3 m_Vertical;
};
