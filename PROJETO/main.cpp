#include "rtproject.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

using namespace std;

int main() {
    hittable_list world;

    auto R = std::cos(pi/4);
    
    auto material_left = make_shared<lambertian>(color(0,0,1));
    auto material_right = make_shared<lambertian>(color(1,0,0));
    
    world.add(make_shared<sphere>(point3(-R,0,-1), R, material_left));
    world.add(make_shared<sphere>(point3(R,0,-1), R, material_right));


    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50; 

    cam.vfov = 90;
    
    cam.render(world);
}

/*
Além da nova função `sample_square()` apresentada acima, você também encontrará a função `sample_disk()` no código-fonte do GitHub. 
Ela foi incluída para o caso de você querer experimentar com pixels que não sejam quadrados, mas não a utilizaremos. 
A função `sample_disk()` depende da função `random_in_unit_disk()`, que é definida mais adiante.
*/ 