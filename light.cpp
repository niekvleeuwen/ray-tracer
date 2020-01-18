#include "materials.h"

Light::Light(Vector3D _emitColor){
    emitColor = _emitColor;
}

bool Light::scatter(const Ray &r_in, const objectData &objData, Vector3D &attenuation, Ray&scattered) const { 
    return false; 
}

Vector3D Light::emitted(float u, float v, const Vector3D& p) const {
    return emitColor;
}