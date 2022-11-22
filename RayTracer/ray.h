#ifndef RAY_H
#define RAY_H
#include "vector.h"
class ray {
	vec3 orig;
	vec3 dir;

public:
	ray() {}
	ray(const point3& origin, const vec3& direction);

	vec3 origin() const;
	vec3 direction() const;

	point3 at(double t)const;
};
#endif // !RAY_H
