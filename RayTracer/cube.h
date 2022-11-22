#ifndef CUBE_H
#define CUBE_H
#include "hittable_list.h"
#include "rect.h"
class cube : public hittable {
public:
    point3 box_min;
    point3 box_max;
    hittable_list sides;

    cube() {}
    cube(const point3& p0, const point3& p1, shared_ptr<material> ptr);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const;
};
#endif // !CUBE_H