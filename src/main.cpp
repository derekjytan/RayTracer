#include "../include/rt.h"
// #include <iostream>
#include <cmath>
// #include "../include/color.h"
// #include "../include/vec3.h"
// #include "../include/ray.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"
#include "../include/camera.h"

int main() {
    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;


    // Render
    cam.render(world);
    
    return 0;
}