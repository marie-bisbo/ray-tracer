#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
public:
	Vec3() : vec{ 0, 0, 0 } {}
	Vec3(double vec0, double vec1, double vec2) : vec{ vec0, vec1, vec2 } {}

	double x() const { return vec[0]; }
	double y() const { return vec[1]; }
	double z() const { return vec[2]; }

	Vec3 operator-() const { return Vec3{ -vec[0], -vec[1], -vec[2] }; }
	double operator[](int i) const { return vec[i]; }
	double& operator[](int i) { return vec[i]; }

	Vec3& operator+=(const Vec3& other)
	{
		vec[0] += other.vec[0];
		vec[1] += other.vec[1];
		vec[2] += other.vec[2];
		return *this;
	}

	Vec3& operator*=(const double scalar)
	{
		vec[0] *= scalar;
		vec[1] *= scalar;
		vec[2] *= scalar;
		return *this;
	}

	Vec3& operator/=(const double scalar)
	{
		return *this *= 1 / scalar;
	}

	double Length() const
	{
		return std::sqrt(LengthSquared());
	}

	double LengthSquared() const
	{
		return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	}

public:
	double vec[3];
};

using Point3 = Vec3;
using Colour = Vec3;
