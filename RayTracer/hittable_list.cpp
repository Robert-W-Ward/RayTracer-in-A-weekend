#include "hittable_list.h"

hittable_list::hittable_list(shared_ptr<hittable_list> object) { add(object); }
void hittable_list::clear() { objects.clear(); }
void hittable_list::add(shared_ptr<hittable> obj) { objects.push_back(obj); }
bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
bool hittable_list::bounding_box(double time0, double time1, aabb& output)const {
    if (objects.empty()) return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto& object : objects) {
        if (!object->bounding_box(time0, time1, temp_box)) return false;
        output = first_box ? temp_box : surrounding_box(output, temp_box);
        first_box = false;
    }

    return true;
}
