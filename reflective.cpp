#include "materials.h"

Reflective::Reflective(const Vector3D &a){
    albedo = a;
}

bool Reflective::scatter(const Ray &r_in, const objectData &objData, Vector3D &attenuation, Ray &scattered) const  {
    Vector3D reflected = reflect(unit_vector(r_in.getDirection()), objData.normal);
    scattered = Ray(objData.p, reflected);
    attenuation = albedo;
    return (dot(scattered.getDirection(), objData.normal) > 0);
}

Vector3D Reflective::reflect(const Vector3D &v, const Vector3D &n) const {
     return v - 2*dot(v,n)*n;
}