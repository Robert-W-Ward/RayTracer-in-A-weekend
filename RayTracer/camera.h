#ifndef CAMERA_H
#define CAMERA_H
#include "ray.h"
#include "common.h"
class camera {
public:
    camera(
        point3 lookfrom,
        point3 lookat,
        vec3 vup,
        double vfov,
        double aspect_ratio,
        double aperture,
        double dist_to_focus,
        double _time0,
        double _time1
    );

    ray get_ray(double s, double t) const;

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif // !CAMERA_H
