#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "basic_object.h"

struct objectData;

class Material  {
    public:
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vec& attenuation, Ray& scattered) const = 0;
        virtual Vec emitted(float u, float v, const Vec& p) const {
            return Vec(0,0,0); // On default return black (for non emitting objects)
        }
};

class Diffuse : public Material {
    public:
        Diffuse(Vec _color){
            color = _color;
        }
        Vec random_in_unit_sphere() const;
        double randomDouble() const;
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vec& attenuation, Ray& scattered) const;
    private:
        Vec color;
};

Vec Diffuse::random_in_unit_sphere() const {
    Vec p;
    do {
        p = 2.0*Vec(randomDouble(),randomDouble(),randomDouble()) - Vec(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}

double Diffuse::randomDouble() const {
    return rand() / (RAND_MAX + 1.0);
}

bool Diffuse::scatter(const Ray &r_in, const objectData &objData, Vec& attenuation, Ray& scattered) const {
    Vec random = random_in_unit_sphere();
    Vec target = objData.p + objData.normal + random;
    scattered = Ray(objData.p, target - objData.p);
    attenuation = color;
    return true;
}

class Light : public Material {
    public:
        Light(Vec _emitColor){
            emitColor = _emitColor;
        }
        virtual bool scatter(const Ray &r_in, const objectData &objData,
            Vec& attenuation, Ray& scattered) const { return false; }
        virtual Vec emitted(float u, float v, const Vec& p) const {
            return emitColor;
        }
    private:
        Vec emitColor;
};

class Reflective : public Material {
    public:
        Reflective(const Vec& a){
            albedo = a;
        }
        Vec reflect(const Vec& v, const Vec& n) const;
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vec& attenuation, Ray& scattered) const  {
            Vec reflected = reflect(unit_vector(r_in.getDirection()), objData.normal);
            scattered = Ray(objData.p, reflected);
            attenuation = albedo;
            return (dot(scattered.getDirection(), objData.normal) > 0);
        }
    private:
        Vec albedo;
};

Vec Reflective::reflect(const Vec& v, const Vec& n) const {
     return v - 2*dot(v,n)*n;
}


#endif