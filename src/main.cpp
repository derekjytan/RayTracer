#include <iostream>
#include "../include/color.h"
#include "../include/vec3.h"
#include "../include/ray.h"

color ray_color(const ray& r) {
    return color(0, 0, 0);
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

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Calcualte the vectors across the horizontal and down the vertical viewport edges
    // u is the horizontal vector, v is the vertical vector
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical deltas 
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate teh location of the upper left pixel 
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) + viewport_v / 2 - viewport_u / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    // Output the image in PPM format
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++) {
        // clog is a standard output stream object for logging messages
        // We'll add a progress indicator to our output to track the progress of the rendering
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {
            // auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.0);

            auto pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\nDone\n";
}