#include "hittable.h"
class xz_rect : public hittable {
public:
    inline xz_rect(){}

    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k,
        std::shared_ptr<material> mat)
        : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
        output_box = aabb(point3(x0, k - 0.0001, z0), point3(x1, k + 0.0001, z1));
        return true;
    }

public:
    std::shared_ptr<material> mp;
    double x0 = 0, x1 = 0, z0 = 0, z1 = 0, k = 0;
};
bool xz_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto t = (k - r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}