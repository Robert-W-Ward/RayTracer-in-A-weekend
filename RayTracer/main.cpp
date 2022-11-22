/////////////////////////////////////////
//Adapted from 
// “Ray Tracing in One Weekend.” raytracing.github.io/books/RayTracingInOneWeekend.html
// (accessed 11.18, 2022)
// My version has phenomenally fewer features and is worse in almost every way 
// BUT it is multithreaded so thats cool
/////////////////////////////////////////
#include <iostream>
#include <future>
#include <fstream>
#include "ray.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "cube.h"
#include "rect.h"
#include "camera.h"
//+x -->, +y^^^ +zoutOfScreen
//-x <--  -yvvv -zintoScreen

color ray_color(const ray& r,color& bg , const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return bg;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, bg, world, depth - 1);
}

hittable_list createScene() {
    hittable_list objects;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto blue = make_shared<lambertian>(color(0, 0, 1));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto Light = make_shared<diffuse_light>(color(15, 15, 15));
    auto darkgrey = make_shared<lambertian>(color(.75, .75, .75));
    auto _lightgrey = make_shared<lambertian>(color(.25, .25, .25));
    auto _glass = make_shared<dielectric>(1.2);
    auto _metal = make_shared<metal>(color(0, 0, 1), 1);
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, darkgrey));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, darkgrey));
    objects.add(make_shared<xz_rect>(113, 443, 127, 432, 554, Light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, red)); // floor
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, blue));//ceiling
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, _lightgrey));

    shared_ptr<hittable> box1 = make_shared<cube>(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared <rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    objects.add(box1);

    objects.add(make_shared<sphere>(point3(300,200,50),50,_glass));
    objects.add(make_shared<sphere>(point3(400, 200, 75), 25, _metal));

    return objects;

}


static color getColor(
    int i,int j,int samples_per_pixel,int image_width,int image_height,
    camera cam,color background,hittable_list world, int max_depth) {

    color pixel_color(0, 0, 0);
    for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, background, world, max_depth);
    }
    return pixel_color;
}

hittable_list random_scene() {
    hittable_list world;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<lambertian>(checker)));

    for (int a = -11; a < 1; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    return world;
}
hittable_list simple_light() {
    hittable_list objects;
    auto pertext = make_shared<solid_color>(color(1,1,1));
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    auto difflight = make_shared<diffuse_light>(color(8, 8, 8));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));

    return objects;
}


std::vector<std::future<color>> futures;
int main() {

    // Image
    auto aspect_ratio = 4.0 / 3.0;
    int image_width = 500;
    int samples_per_pixel = 400;
    const int max_depth = 50;
    std::fstream outFile;

    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    color background(0, 0, 0);
    // World
    hittable_list world;
    auto vfov = 40.0;

    switch (3) {
    case 1:
        world = random_scene();
        background = color(0.7, 0.8, 1.0);
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vfov = 20.0;
        aperture = 0.1;
        break;
    case 2:
        world = simple_light();
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vfov = 20.0;
        break;
    case 3:
        world = createScene();
        aspect_ratio = 1.0;
        image_width = 500;
        samples_per_pixel = 1000;
        background = color(0.5, 0.5, 0.5);
        //lookfrom = point3(0, 5, 15);
        //lookat = point3(0, 0, 0);
        lookat = point3(278, 278, 0);
        lookfrom = point3(278, 278, -800);
        vfov = 40.0;
        break;
    }

    
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    // Render
    auto t1 = std::chrono::high_resolution_clock::now();
    outFile.open("image.ppm", std::ios::out | std::ios::trunc);
    outFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    std::vector<color>* colors =  new std::vector<color>();
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' '<< std::flush;
        for (int i = 0; i < image_width; ++i) {
            //this speeds up renders by like 5x
            futures.push_back(std::async(std::launch::async, getColor,i,j,samples_per_pixel,image_width,image_height,cam,background,world,max_depth));
        }
    }
    size_t current = futures.size();
    std::cerr << '\n';
    for (auto& future: futures)
    {
        current -= 1;
        write_color(outFile, future.get(), samples_per_pixel);
        std::cerr << "\rPixels left to render: " << current<<std::flush;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto mSec = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
    std::cerr << "\nDone.\n";
    outFile.close();
    std::cerr << "Elapsed time: " << mSec.count() << " s\n";
}