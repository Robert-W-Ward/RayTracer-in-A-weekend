#ifndef AABB_H
#define AABB_H
#include "ray.h"
class aabb {
public:
    point3 minimum;
    point3 maximum;

    aabb();
    aabb(const point3& a, const point3& b);

    point3 min()const;
    point3 max()const;
    bool hit(const ray& r, double t_min, double t_max) const;
    double area() const;
    int longest_axis() const;
    
};
extern aabb surrounding_box(aabb& a, aabb& b);
#endif // !AABB_H
