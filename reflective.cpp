#include "materials.h"

Reflective::Reflective(const Vec &a){
    albedo = a;
}

bool Reflective::scatter(const Ray &r_in, const objectData &objData, Vec &attenuation, Ray &scattered) const  {
    Vec reflected = reflect(unit_vector(r_in.getDirection()), objData.normal);
    scattered = Ray(objData.p, reflected);
    attenuation = albedo;
    return (dot(scattered.getDirection(), objData.normal) > 0);
}

Vec Reflective::reflect(const Vec &v, const Vec &n) const {
     return v - 2*dot(v,n)*n;
}