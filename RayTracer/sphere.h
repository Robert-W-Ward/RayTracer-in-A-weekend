#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"
class sphere :public hittable {

	static void get_sphere_uv(const point3& p, double& u, double& v);

	public:
		point3 center;
		double radius = 0.0;
		std::shared_ptr<material> mat_ptr;

		sphere();
		sphere(point3 cen, double r, shared_ptr<material> m);

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec)const override;
		virtual bool bounding_box(double time0, double time1, aabb& output)const override;
};
#endif // !SPHERE_H