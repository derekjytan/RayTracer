#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "color.h"
#include "interval.h"

class camera {
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int samples_per_pixel = 10;
        int max_depth = 10;
        
        void render(const hittable& world) {
            initialize();

            // Output the image in PPM format
            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

            for (int j = image_height - 1; j >= 0; --j) {
                // clog is a standard output stream object for logging messages
                // We'll add a progress indicator to our output to track the progress of the rendering
                std::clog << "\rScanlines remaining: " << j << ' ' << std::flush;
                for (int i = 0; i < image_width; ++i) {
                    color pixel_color(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r,max_depth, world);
                    } 
                    write_color(std::cout, pixel_color / samples_per_pixel);
                }
            }   
            std::clog << "\nDone\n";
        }

    private:
        int image_height;
        point3 camera_center;
        double focal_length;
        vec3 horizontal;
        vec3 vertical;
        vec3 lower_left_corner;
        double pixel_samples_scale;
        point3 pixel00_loc;      // Location of pixel 0, 0
        vec3 pixel_delta_u;      // Offset to pixel to the right
        vec3 pixel_delta_v;      // Offset to pixel below

        void initialize() {
            // Calculate image height based on aspect ratio
            image_height = static_cast<int>(image_width / aspect_ratio);
            if (image_height < 1) image_height = 1;

            pixel_samples_scale = 1.0 / samples_per_pixel;
            
            focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width) / image_height);
            camera_center = point3(0, 0, 0);

            // Calculate the vectors across the horizontal and down the vertical viewport edges
            // u is the horizontal vector, v is the vertical vector
            horizontal = vec3(viewport_width, 0, 0);
            vertical = vec3(0, viewport_height, 0);
            
            // Calculate the lower left corner of the viewport
            lower_left_corner = camera_center - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
            
            // Calculate pixel deltas and pixel00 location
            pixel_delta_u = horizontal / image_width;
            pixel_delta_v = vertical / image_height;
            
            // Calculate the location of the upper left pixel
            pixel00_loc = lower_left_corner + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        ray get_ray(int i, int j) const {
            // Construct a camera ray originating from the origin and directed at randomly sampled points
            // on the pixel location i, j

            auto offset = sample_square();
            auto pixel_sample = pixel00_loc
                + ((i + offset.x()) * pixel_delta_u)
                + ((j + offset.y()) * pixel_delta_v);
            
            auto ray_origin = camera_center;
            auto ray_direction = pixel_sample - ray_origin;
            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const {
            // Get a random point in the square surrounding the origin and scale it up to [-1, 1]
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        color ray_color(const ray& r, int depth,const hittable& world) const {
            if (depth <= 0) return color(0, 0, 0);
            hit_record rec;
            if (world.hit(r, interval(0.001, infinity), rec)) {
                vec3 direction = random_on_hemisphere(rec.normal);
                return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
            }
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
        }
};


#endif