// Add a class that stores a list of hittable objects

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

// new c++ features:

/*
shared_ptr<type> is a pointer to some allocated memory of type, with reference counting semantics. 
everytime i assign its value to another shared pointer, the reference count is incremented.
as they go out of scope, the reference count is decremented.
once the reference count reaches 0, the memory is automatically deallocated.

make_shared<type>(args) allocates a new instance of type thing, using the constructor parameters. 
It returns a shared_ptr<thing>

*/

class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {} // Default constructor
        hittable_list(shared_ptr<hittable> object) { add(object); } // Constructor with one object

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) {
            // Add an object to the end of the list, push_back is a method that comes from std::vector
            objects.push_back(object);
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            for (const auto& object : objects) {
                if (object -> hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
            return hit_anything;
        }
};

#endif