#pragma once
#include "vector.h"
class ray {
	vec3 orig;
	vec3 dir;

public:
	ray() {}
	ray(const point3& origin,const vec3& direction):orig(origin),dir(direction){}

	vec3 origin() const { return orig; }
	vec3 direction() const { return dir; }

	point3 at(double t)const {
		return orig + t * dir;
	}
};

