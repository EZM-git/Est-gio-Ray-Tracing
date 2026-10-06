#include "rtproject.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

using namespace std;

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_bubble = make_shared<dielectric>(1.0 / 1.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    world.add(make_shared<sphere>(point3(0, 0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1, 0, -1), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, material_right));
    
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50; 

    cam.vfov = 90;
    cam.lookfrom = point3(-2, 2, 1);
    cam.lookat = point3(0, 0, -1);
    cam.vup = vec3(0, 1 ,0);
    
    cam.render(world);
}

/*
Além da nova função `sample_square()` apresentada acima, você também encontrará a função `sample_disk()` no código-fonte do GitHub. 
Ela foi incluída para o caso de você querer experimentar com pixels que não sejam quadrados, mas não a utilizaremos. 
A função `sample_disk()` depende da função `random_in_unit_disk()`, que é definida mais adiante.
*/ 