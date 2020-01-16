#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "basic_object.h"

struct hit_record;

Vec reflect(const Vec& v, const Vec& n) {
     return v - 2*dot(v,n)*n;
}

double randomDouble(){
    return rand() / (RAND_MAX + 1.0);
}

Vec random_in_unit_sphere() {
    Vec p;
    do {
        p = 2.0*Vec(randomDouble(),randomDouble(),randomDouble()) - Vec(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}

class material  {
    public:
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec& attenuation, Ray& scattered) const = 0;
        virtual Vec emitted(float u, float v, const Vec& p) const {
            return Vec(0,0,0); // On default return black (for non emitting objects)
        }
};

class Diffuse : public material {
    public:
        Diffuse(Vec _color){
            color = _color;
        }
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec& attenuation, Ray& scattered) const {
            Vec target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = Ray(rec.p, target - rec.p);
            attenuation = color;
            return true;
        }
    private:
        Vec color;
};

class Light : public material {
    public:
        Light(Vec _emitColor){
            emitColor = _emitColor;
        }
        virtual bool scatter(const Ray& r_in, const hit_record& rec,
            Vec& attenuation, Ray& scattered) const { return false; }
        virtual Vec emitted(float u, float v, const Vec& p) const {
            return emitColor;
        }
    private:
        Vec emitColor;
};

class Reflective : public material {
    public:
        Reflective(const Vec& a){
            albedo = a;
        }
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec& attenuation, Ray& scattered) const  {
            Vec reflected = reflect(unit_vector(r_in.getDirection()), rec.normal);
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.getDirection(), rec.normal) > 0);
        }
    private:
        Vec albedo;
};

#endif