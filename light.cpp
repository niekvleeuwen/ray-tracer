#include "materials.h"

Light::Light(Vec _emitColor){
    emitColor = _emitColor;
}

bool Light::scatter(const Ray &r_in, const objectData &objData, Vec &attenuation, Ray&scattered) const { 
    return false; 
}

Vec Light::emitted(float u, float v, const Vec& p) const {
    return emitColor;
}