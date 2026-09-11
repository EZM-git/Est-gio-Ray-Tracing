#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "rtproject.h"  // Esta biblioteca traz ferramentas para gerenciar a memória do computador de forma automática e segura
                   // É ela quem define o shared_ptr e o make_shared
#include <vector>  // Esta biblioteca libera o std::vector, que funciona como uma lista/array que pode crescer ou diminuir de tamanho 
                   // dinamicamente enquanto o programa roda.

class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;  // um ponteiro inteligente que tem uma lista que pode aumentar ou diminuir

        hittable_list() {}  // lista vazia
        hittable_list(shared_ptr<hittable> object) { add(object); } // cria a lista e add o objeto

        void clear() { objects.clear(); } // da clear na lista

        void add(shared_ptr<hittable> object){
            objects.push_back(object);
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            hit_record temp_rec; // estr temporaria
            bool hit_anything = false;
            auto closest_so_far = ray_t.max; // dist do obj mais longe

            for (const auto& object : objects) {
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
            return hit_anything;  // se um obj esta atras de outro, irá ignorá-lo
        }

};


#endif