#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}
        // functions ray::origin() and ray::direction() return immutable references to their members
        // Callers can either use the reference directly or copy the reference to a local variable
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
        point3 origin() const { return orig; }
        vec3 direction() const { return dir; }

        point3 at(double t) const {
            return orig + t * dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif