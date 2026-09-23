#include "rtproject.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

using namespace std;

int main() {
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5)); // bola
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100)); // chao

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