#ifndef RECT_H
#define RECT_H
#include "hittable.h"
class xy_rect :public hittable
{
public:
    std::shared_ptr<material> mp;
    double x0 = 0, x1 = 0, y0 = 0, y1 = 0, k = 0;

    xy_rect();
    xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<material> mat);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

};
class xz_rect : public hittable {
public:
    std::shared_ptr<material> mp;
    double x0 = 0, x1 = 0, z0 = 0, z1 = 0, k = 0;
    
    xz_rect() {}
    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k,std::shared_ptr<material> mat);
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
};
class yz_rect : public hittable {
public:
    std::shared_ptr<material> mp;
    double y0 = 0, y1 = 0, z0 = 0, z1 = 0, k = 0;

    yz_rect() {}
    yz_rect(double _y0, double _y1, double _z0, double _z1, double _k,std::shared_ptr<material> mat);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
};
#endif // !RECT_H
