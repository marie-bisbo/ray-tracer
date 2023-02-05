#pragma once

#include "vec3.h"

#include <iostream>

void WriteColour(std::ostream& out, Colour pixelColour)
{
	out << static_cast<int>(255.999 * pixelColour.x()) << ' '
		<< static_cast<int>(255.999 * pixelColour.y()) << ' '
		<< static_cast<int>(255.999 * pixelColour.z()) << '\n';
}
