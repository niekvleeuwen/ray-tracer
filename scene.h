#ifndef HITABLELISTH
#define HITABLELISTH

#include "basic_object.h"
#include "material.h"
#include "camera.h"

class Scene: public BasicObject  {
    public:
        Scene() {}
        Scene(BasicObject **_list, int _listSize, Camera cam);
        Vec trace(const Ray& r, int depth);
        Vec getColor(double u, double v);
        virtual bool hit(const Ray& r, double tmin, double tmax, objectData& rec) const;
    private:
        Camera cam;
        BasicObject **list;
        int listSize;
};

Scene::Scene(BasicObject **_list, int _listSize, Camera _cam){
    cam = _cam;
    list = _list; 
    listSize = _listSize;
}

Vec Scene::getColor(double u, double v){
    Ray r = cam.getRay(u, v);
    return this->trace(r, 0);
}

Vec Scene::trace(const Ray& r, int depth) {
    objectData rec;
    // Check if the ray hits something
    if (this->hit(r, 0.001, MAXFLOAT, rec)) {
        Ray scattered;
        Vec attenuation;
        Vec emitted = rec.currentMaterial->emitted(rec.u, rec.v, rec.p);
        if (depth < 25 && rec.currentMaterial->scatter(r, rec, attenuation, scattered))
             return emitted + attenuation*trace(scattered, depth+1);
        else
            return emitted;
    }else{
        // Return black if the ray hits nothing
        return Vec(0,0,0);
    }
}

bool Scene::hit(const Ray& r, double t_min, double t_max, objectData& rec) const {
    objectData tmp;
    bool hit_anything = false;
    double currentClosest = t_max;
    for (int i = 0; i < listSize; i++) {
        if (list[i]->hit(r, t_min, currentClosest, tmp)){
            hit_anything = true;
            currentClosest = tmp.t;
            rec = tmp;
        }
    }
    return hit_anything;
}


#endif
