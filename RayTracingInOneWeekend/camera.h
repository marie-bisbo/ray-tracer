#pragma once

#include "vec3.h"
#include "ray.h"

class Camera
{
public:
	Camera(
		Point3 lookFrom,
		Point3 lookAt,
		Vec3 verticalUp,
		double verticalFOV,
		double aspectRatio,
		double aperture,
		double focusDistance)
	{
		auto theta = DegreesToRadians(verticalFOV);
		auto h = tan(theta / 2);
		auto viewportHeight = 2.f * h;
		auto viewportWidth = aspectRatio * viewportHeight;

		m_W = UnitVector(lookFrom - lookAt);
		m_U = UnitVector(Cross(verticalUp, m_W));
		m_V = Cross(m_W, m_U);

		m_Origin = lookFrom;
		m_Horizontal = focusDistance * viewportWidth * m_U;
		m_Vertical = focusDistance * viewportHeight * m_V;
		m_LowerLeftCorner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - focusDistance * m_W;

		m_LensRadius = aperture / 2;
	}

	Ray GetRay(const double s, const double t) const
	{
		Vec3 radiusDisk = m_LensRadius * RandomPointInUnitDisk();
		Vec3 offset = m_U * radiusDisk.x() + m_V * radiusDisk.y();
		
		return Ray(m_Origin + offset, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin - offset);
	}

private:
	Point3 m_Origin;
	Vec3 m_Horizontal;
	Vec3 m_Vertical;
	Point3 m_LowerLeftCorner;
	Vec3 m_U, m_V, m_W;
	double m_LensRadius;
};
