#include "materials.h"

Diffuse::Diffuse(Vec _color){
    color = _color;
}

Vec Diffuse::random_in_unit_sphere() const {
    Vec p;
    do {
        p = 2.0*Vec(randomDouble(),randomDouble(),randomDouble()) - Vec(1,1,1);
    } while (p.notSquaredLength() >= 1.0);
    return p;
}

double Diffuse::randomDouble() const {
    return rand() / (RAND_MAX + 1.0);
}

bool Diffuse::scatter(const Ray &r_in, const objectData &objData, Vec &attenuation, Ray &scattered) const {
    Vec random = random_in_unit_sphere();
    Vec target = objData.p + objData.normal + random;
    scattered = Ray(objData.p, target - objData.p);
    attenuation = color;
    return true;
}