#include "materials.h"

Diffuse::Diffuse(Vector3D _color){
    color = _color;
}

Vector3D Diffuse::random_in_unit_sphere() const {
    Vector3D p;
    do {
        p = 2.0*Vector3D(randomDouble(),randomDouble(),randomDouble()) - Vector3D(1,1,1);
    } while (p.notSquaredLength() >= 1.0);
    return p;
}

double Diffuse::randomDouble() const {
    return rand() / (RAND_MAX + 1.0);
}

bool Diffuse::scatter(const Ray &r_in, const objectData &objData, Vector3D &attenuation, Ray &scattered) const {
    Vector3D random = random_in_unit_sphere();
    Vector3D target = objData.p + objData.normal + random;
    scattered = Ray(objData.p, target - objData.p);
    attenuation = color;
    return true;
}