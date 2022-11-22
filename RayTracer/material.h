#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"
#include "ray.h"
#include "texture.h"
#include "hittable_list.h"
class material {
	public:
		static int materialCnt;
		virtual color emitted(double u, double v, const point3& p)const;
		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)const = 0;
};
class lambertian : public material {
	public:
		shared_ptr<texture> albedo;
		lambertian(const color& a);
		lambertian(shared_ptr<texture> a);
		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)const override;		
};
class metal : public material {
public:
	color albedo;
	double fuzz;
	metal(const color& a, double f);
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};
class dielectric : public material {
public:
	double ir; // Index of Refraction
	dielectric(double index_of_refraction);
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
private:
	static double reflectance(double cosine, double ref_idx);
};
class diffuse_light :public material {
	public:
		shared_ptr<texture>emit;
		diffuse_light(shared_ptr<texture> a);
		diffuse_light(color c);
		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)const override;
		virtual color emitted(double u, double v, const point3& p) const override;
};
#endif // !MATERIAL_H