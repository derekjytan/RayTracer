#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

// Color utility functions

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    // Write the translated [0,255] value of each color component
    auto red = pixel_color.x();
    auto green = pixel_color.y();
    auto blue = pixel_color.z();

    // Translate the [0, 1] component values to the byte range [0, 255]
    static const interval intensity(0.000, 0.999);
    int red_byte = int(256 * intensity.clamp(red));
    int green_byte = int(256 * intensity.clamp(green));
    int blue_byte = int(256 * intensity.clamp(blue));

    // Write out the pixel color components
    out << red_byte << ' ' << green_byte << ' ' << blue_byte << '\n';
}

#endif