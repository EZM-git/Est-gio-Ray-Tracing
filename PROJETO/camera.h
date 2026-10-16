#ifndef CAMERA_H
#define CAMERA_H

#include "material.h"
#include "rtproject.h"
#include "hittable.h"
#include "hittable_list.h"

class camera {
    public:
        double aspect_ratio = 1.0; // ratio largura sobre altura
        int image_width = 100; // img renderizada largura em pixels
        int samples_per_pixel = 10; // qtd de bglh aleatorio por pixel
        int max_depth = 10; // profundidade max q pode ir

        double vfov = 90; // Ângulo de visão vertical em graus
        point3 lookfrom = point3(0, 0, 0); // de onde a câmera vem
        point3 lookat = point3(0, 0, -1); // pra onde a câmera ta olhando
        vec3 vup = vec3(0, 1, 0); // Camera-relative "up" direction?

        double defocus_angle = 0;  
        double focus_dist = 10;   


        void render(const hittable& world){
            initialize();
            
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++ ){
                std::clog << "\rScanlines remaining: " << (image_height - j) << " \n";
                for (int i = 0; i < image_width; i++) {
                    color pixel_color(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++){
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);  // escrevendo as cores
                }
            }
            
            std::clog << "\nCABO.             \n";
        }  

    private:
        int    image_height;    // Altura da imagem renderizada
        double pixel_samples_scale;
        point3 center;          // Centro da câmera
        point3 pixel00_loc;     // Localização do pixel 0, 0
        vec3   pixel_delta_u;   // Deslocamento de um pixel para a direita
        vec3   pixel_delta_v;   // Deslocamento para o pixel abaixo
        vec3   u, v, w;
        vec3   defocus_disk_u;       
        vec3   defocus_disk_v;      

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height; // If true img_h = 1, senão i_h = img_h
            
            pixel_samples_scale = 1.0 / samples_per_pixel;
            
            center = lookfrom;

            // Determinar as dimensões do vp
            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta/2);
            auto vp_height = 2 * h * focus_dist;
            auto vp_width = vp_height * (double(image_width)/image_height);

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);
            
            // Calcule os vetores ao longo das bordas horizontal e vertical da viewport 
            vec3 vp_u = vp_width * u; // vp inteiro hor
            vec3 vp_v = vp_height * -v; // msm soq ver

            // Calcula os vetores delta horizontal e vertical de pixel para pixel
            pixel_delta_u = vp_u / image_width; // 1 pixel hor
            pixel_delta_v = vp_v / image_height; // 1 pixel ver

            // Calcula a localização do pixel superior esquerdo ?? Porque
            auto vp_upper_left = center - (focus_dist * w) - vp_u/2 - vp_v/2;
            pixel00_loc = vp_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

            auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }
        
        ray get_ray(int i, int j) const {
            // raio q vem da origem até o lugar aleatorio
            // aponta para a localização em volta do pixel: i, j

            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

            auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
            auto ray_direction = pixel_sample - ray_origin;
            auto ray_time = random_double(0.0, 1.0); // tempo aleatorio entre 0 e 1

            return ray(ray_origin, ray_direction, ray_time);
        }

        vec3 sample_square() const {
            // retorna o vetor para um ponto aleatório em [-.5, -.5] - [+.5, +.5] unidade do quadrado
            // isso seria a metado do pixel q ele ta indo no ponto aleatório, por isso .5 -- metade do pixel
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        point3 defocus_disk_sample() const {
            auto p = random_in_unit_disk();
            return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
        }

        color ray_color(const ray& r, int depth, const hittable& world) const { 
            // se passar do limite de profundidade, n terá luz
            if (depth <= 0)
                return color(0, 0, 0);
            hit_record rec;
            
            // rec.t                  distância do raio até o impacto
            // rec.p                  ponto do impacto
            // rec.normal             normal da superfície
            // rec.front_face         se o raio atingiu a frente da superfície

            if (world.hit(r, interval(0.001, infinity), rec)) {
                ray scattered;
                color attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, depth-1, world);
            
                return color(0, 0, 0);
            }
            
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};



#endif