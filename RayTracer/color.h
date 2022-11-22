#ifndef COLOR_H
#define COLOR_H
#include "common.h"
#include "vector.h"
extern double clamp(double x,double min,double max);
void write_color(std::ostream& out, color pixel_color, int samples_per_pixel);
#endif // !COLOR_H
