#ifndef HITTABLE_H
#define HITTABLE_H
#include "common.h"
#include "aabb.h"
class material;
struct hit_record {
	point3 p;
	vec3 normal;
	std::shared_ptr<material> mat_ptr;
	double t=0;
	double u=0;
	double v=0;
	bool front_face;
    void set_face_normal(const ray& r, const vec3& outward_normal);
};
class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec)const = 0;
	virtual bool bounding_box(double time0, double time1, aabb& output)const = 0;
};
class translate : public hittable {
public:
    shared_ptr<hittable> ptr;
    vec3 offset;
    translate(shared_ptr<hittable> p, const vec3& displacement);
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

};
class rotate_y : public hittable {
public:
    shared_ptr<hittable> ptr;
    double sin_theta;
    double cos_theta;
    bool hasbox;
    aabb bbox;

    rotate_y(std::shared_ptr<hittable> p, double angle);
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
};
#endif // !HITTABLE_H