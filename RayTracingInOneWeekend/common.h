#pragma once

#include <cmath>
#include <limits>
#include <memory>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions

inline double DegreesToRadians(double degrees)
{
	return degrees * pi / 180.f;
}


