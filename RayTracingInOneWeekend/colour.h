#pragma once

#include "vec3.h"
#include "common.h"

#include <iostream>

void WriteColour(std::ostream& out, Colour pixelColour, int samplesPerPixel)
{
	auto r = pixelColour.x();
	auto g = pixelColour.y();
	auto b = pixelColour.z();

	// Divide the colour by the number of samples

	auto scale = 1.f / samplesPerPixel;
	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);
;

	// Write the translated [0, 255] value of each colour component 
	out << static_cast<int>(256 * Clamp(r, 0.f, 0.999f)) << ' '
		<< static_cast<int>(256 * Clamp(g, 0.f, 0.999f)) << ' '
		<< static_cast<int>(256 * Clamp(b, 0.f, 0.999f)) << '\n';
}
