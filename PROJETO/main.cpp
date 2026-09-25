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
    auto material_center = make_shared<lambertian>(color(0.2, 0.6, 0.3));
    auto material_left = make_shared<metal>(color(0.1, 0.2, 0.2));
    auto material_right = make_shared<metal>(color(0.8, 0.3, 0.1));

    world.add(make_shared<sphere>(point3(0, -100.5, -1.0), 100, material_ground)); // bola do chao man, e x y e z nessa ordem certo
    world.add(make_shared<sphere>(point3(0, 0, -1.2), 0.5, material_center)); // bola do meio
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5, material_left)); // bola da esquerda
    world.add(make_shared<sphere>(point3(1, 0, -1.0), 0.5, material_right)); // bola da direita

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50; 

    cam.render(world);
}

/*
Além da nova função `sample_square()` apresentada acima, você também encontrará a função `sample_disk()` no código-fonte do GitHub. 
Ela foi incluída para o caso de você querer experimentar com pixels que não sejam quadrados, mas não a utilizaremos. 
A função `sample_disk()` depende da função `random_in_unit_disk()`, que é definida mais adiante.
*/ 