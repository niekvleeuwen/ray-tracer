#ifndef HITABLELISTH
#define HITABLELISTH

#include "basic_object.h"
#include "material.h"

class Scene: public BasicObject  {
    public:
        Scene() {}
        Scene(BasicObject **l, int n) { list = l; list_size = n; }
        Vec color(const Ray& r, int depth);
        virtual bool hit(const Ray& r, double tmin, double tmax, hit_record& rec) const;
        BasicObject **list;
        int list_size;
};

Vec Scene::color(const Ray& r, int depth) {
    hit_record rec;
    if (this->hit(r, 0.001, MAXFLOAT, rec)) {
        Ray scattered;
        Vec attenuation;
        Vec emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (depth < 25 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
             return emitted + attenuation*color(scattered, depth+1);
        else
            return emitted;
    }else{
        return Vec(0,0,0);
    }
}

bool Scene::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}


#endif
