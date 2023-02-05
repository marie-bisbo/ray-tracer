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

// Utility functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& vector)
{
	return out << vector.vec[0] << vector.vec[1] << vector.vec[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(u.vec[0] + v.vec[0], u.vec[1] + v.vec[1], u.vec[2] + v.vec[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(u.vec[0] - v.vec[0], u.vec[1] - v.vec[1], u.vec[2] - v.vec[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return Vec3(u.vec[0] * v.vec[0], u.vec[1] * v.vec[1], u.vec[2] * v.vec[2]);
}

inline Vec3 operator*(double scalar, const Vec3& v)
{
	return Vec3(scalar * v.vec[0], scalar * v.vec[1], scalar * v.vec[2]);
}

inline Vec3 operator*(const Vec3& v, double scalar)
{
	return scalar * v;
}

inline Vec3 operator/(const Vec3& v, double scalar)
{
	return (1 / scalar) * v;
}

inline double Dot(const Vec3& u, const Vec3& v)
{
	return u.vec[0] * v.vec[0] + u.vec[1] * v.vec[1] + u.vec[2] * v.vec[2];
}

inline Vec3 Cross(const Vec3& u, const Vec3& v) 
{
	return Vec3(u.vec[1] * v.vec[2] - u.vec[2] * v.vec[1],
		u.vec[2] * v.vec[0] - u.vec[0] * v.vec[2],
		u.vec[0] * v.vec[1] - u.vec[1] * v.vec[0]);
}

inline Vec3 UnitVector(const Vec3 v)
{
	return v / v.Length();
}

