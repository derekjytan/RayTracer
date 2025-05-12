#ifndef RT_H
#define RT_H

#include <cmath>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>
#include <random>

#include "interval.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"

// C++ std usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min, max)
    return min + (max - min) * random_double();
}

// inline double random_double() {
//     static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//     static std::mt19937 generator;
//     return distribution(generator);
// }

// Common Headers
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif