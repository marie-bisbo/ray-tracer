#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Constants

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility functions

inline double DegreesToRadians(const double degrees)
{
	return degrees * pi / 180.f;
}

inline double GenerateRandomDoubleNormalised()
{
	return rand() / (RAND_MAX + 1.f);
}

inline double GenerateRandomDouble(const double min, const double max)
{
	return min + (max - min) * GenerateRandomDoubleNormalised();
}

inline double Clamp(const double value, const double min, const double max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}


