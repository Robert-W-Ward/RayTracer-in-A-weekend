#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include "common.h"
class vec3 {
public: 
	double e[3];
	vec3();
	vec3(double x, double y, double z);


	//member function declarations
	double x() const;
	double y() const;
	double z() const;

	vec3 operator-() const;
	double operator[](int i) const;
	double& operator[](int i);

	vec3& operator+=(const vec3& v);
	vec3& operator*=(const double t);
	vec3& operator/=(const double t);

	double length() const;
	double length_squared() const;
	static vec3 random();
	static vec3 random(double min, double max);
	bool near_zero()const;

};
using point3 = vec3;
using color = vec3;
//non-member function declarations 
extern std::ostream& operator<<(std::ostream& out, const vec3& v);
extern vec3 operator+(const vec3& u, const vec3& v);
extern vec3 operator-(const vec3& u, const vec3& v);
extern vec3 operator*(const vec3& u, const vec3& v);
extern vec3 operator*(double t, const vec3& v);
extern vec3 operator*(const vec3& u, double t);
extern vec3 operator/(vec3 u, double t);
//non-member vector operation
extern double dot(const vec3& u, const vec3& v);
extern vec3 cross(const vec3& u, const vec3& v);
extern vec3 unit_vector(vec3 v);
extern vec3 random_in_unit_sphere();
extern vec3 random_unit_vector();
extern vec3 random_in_hemisphere(const vec3& normal);
extern vec3 reflect(const vec3& v, const vec3& n);
extern vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);
#endif // !VECTOR_H