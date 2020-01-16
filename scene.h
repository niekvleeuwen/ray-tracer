#ifndef HITABLELISTH
#define HITABLELISTH

#include "basic_object.h"
#include "material.h"
#include "camera.h"

class Scene: public BasicObject  {
    public:
        Scene() {}
        Scene(BasicObject **_list, int _list_size, Camera cam);
        Vec trace(const Ray& r, int depth);
        Vec getColor(double u, double v);
        virtual bool hit(const Ray& r, double tmin, double tmax, hit_record& rec) const;
    private:
        Camera cam;
        BasicObject **list;
        int list_size;
};

Scene::Scene(BasicObject **_list, int _list_size, Camera _cam){
    cam = _cam;
    list = _list; 
    list_size = _list_size;
}

Vec Scene::getColor(double u, double v){
    Ray r = cam.getRay(u, v);
    return this->trace(r, 0);
}

Vec Scene::trace(const Ray& r, int depth) {
    hit_record rec;
    if (this->hit(r, 0.001, MAXFLOAT, rec)) {
        Ray scattered;
        Vec attenuation;
        Vec emitted = rec.currentMaterial->emitted(rec.u, rec.v, rec.p);
        if (depth < 25 && rec.currentMaterial->scatter(r, rec, attenuation, scattered))
             return emitted + attenuation*trace(scattered, depth+1);
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
