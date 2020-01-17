#include "scene.h"

Scene::Scene(BasicObject **_list, int _listSize){
    list = _list; 
    listSize = _listSize;
}

void Scene::setCamera(Camera *_cam){
    cam = _cam;
}

// This function takes the x,y and returns to color for that given pixel
Vec Scene::getColor(double x, double y){
    Ray r = cam->getRay(x, y);
    return this->trace(r, 0);
}

Vec Scene::trace(const Ray &r, int depth) {
    objectData objData;
    // Check if the ray hits something
    if (this->hit(r, 0.001, MAXFLOAT, objData)) {
        Ray scattered;
        Vec attenuation;
        Vec emitted = objData.currentMaterial->emitted(objData.u, objData.v, objData.p);
        if (depth < 25 && objData.currentMaterial->scatter(r, objData, attenuation, scattered))
             return emitted + attenuation*trace(scattered, depth+1);
        else
            return emitted;
    }else{
        // Return black if the ray hits nothing
        return Vec(0,0,0);
    }
}

bool Scene::hit(const Ray &r, double t_min, double t_max, objectData &objData) const {
    objectData tmp;
    bool hit_anything = false;
    double currentClosest = t_max;
    for (int i = 0; i < listSize; i++) {
        if (list[i]->hit(r, t_min, currentClosest, tmp)){
            hit_anything = true;
            currentClosest = tmp.t;
            objData = tmp;
        }
    }
    return hit_anything;
}

