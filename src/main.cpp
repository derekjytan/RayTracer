#include "../include/rt.h"
// #include <iostream>
#include <cmath>
// #include "../include/color.h"
// #include "../include/vec3.h"
// #include "../include/ray.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"


// Create a sphere 
// double hit_sphere(const point3& center, double radius, const ray& r) {
//     vec3 oc = center - r.origin();
    // auto a = dot(r.direction(), r.direction());
    // auto b = -2.0 * dot(r.direction(), oc);
    // auto c = dot(oc, oc) - radius * radius;
    // Quadratic formula
    // auto discriminant = b * b - 4 * a * c;

    // Simplify the ray-sphere function
//     auto a = r.direction().length_squared();
//     auto h = dot(r.direction(), oc);
//     auto c = oc.length_squared() - radius * radius;
//     auto discriminant = h * h - a * c;

//     if (discriminant < 0) {
//         return -1.0;
//     } else {
//         return (h - std::sqrt(discriminant)) / a;
//     }
// }

color ray_color(const ray& r, const hittable& world) {
    // Fill in the ray color to implement a blue gradient
    // Lerp between two values based on the ray direction

    // blendedValue = (1 - a) * startValue + a * endValue
    // a is a value between 0 and 1 that represents the interpolation factor
    // startValue is the starting value
    // endValue is the ending value
    // blendedValue is the interpolated value
    // a is the interpolation factor

    // auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    // if (t > 0.0) {
    //     vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
    //     return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    // }

    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    
    // Background gradient
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    // Calculate the image height, and ensure it's at least 1
    int image_height = int(image_width / aspect_ratio);
    // We don't want it to have a negative height as that can change the aspect ratio
    if (image_height < 1) {
        image_height = 1;
    }

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    // u is the horizontal vector, v is the vertical vector
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = camera_center - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render

    // Output the image in PPM format
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        // clog is a standard output stream object for logging messages
        // We'll add a progress indicator to our output to track the progress of the rendering
        std::clog << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(camera_center, lower_left_corner + u*horizontal + v*vertical - camera_center);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\nDone\n";
}