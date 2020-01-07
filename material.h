#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "basic_object.h"
#include "random.h"
#include "texture.h"

struct hit_record;

Vec reflect(const Vec& v, const Vec& n) {
     return v - 2*dot(v,n)*n;
}


Vec random_in_unit_sphere() {
    Vec p;
    do {
        p = 2.0*Vec(random_double(),random_double(),random_double()) - Vec(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}


class material  {
    public:
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec& attenuation, Ray& scattered) const = 0;
        virtual Vec emitted(float u, float v, const Vec& p) const {
            return Vec(0,0,0);
        }
};


class diffuse : public material {
    public:
        diffuse(const Vec& a){
            albedo = a;
        }
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec& attenuation, Ray& scattered) const  {
             Vec target = rec.p + rec.normal + random_in_unit_sphere();
             scattered = Ray(rec.p, target-rec.p);
             attenuation = albedo;
             return true;
        }
    private:
        Vec albedo;
};

class lambertian : public material {
    public:
        lambertian(texture *a){
            albedo = a;
        }
        virtual bool scatter(const Ray& r_in, const hit_record& rec,
                             Vec& attenuation, Ray& scattered) const {
            Vec target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = Ray(rec.p, target - rec.p);
            attenuation = albedo->value(0, 0, rec.p);
            return true;
        }
    private:
        texture *albedo;
};

class diffuse_light : public material {
    public:
        diffuse_light(texture *a){
            emit = a;
        }
        virtual bool scatter(const Ray& r_in, const hit_record& rec,
            Vec& attenuation, Ray& scattered) const { return false; }
        virtual Vec emitted(float u, float v, const Vec& p) const {
            return emit->value(u, v, p);
        }
    private:
        texture *emit;
};

class metal : public material {
    public:
        metal(const Vec& a, float f){
            albedo = a;
            if (f < 1){
                fuzz = f; 
            }else{
                fuzz = 1; 
            }
        }
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec& attenuation, Ray& scattered) const  {
            Vec reflected = reflect(unit_vector(r_in.getDirection()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.getDirection(), rec.normal) > 0);
        }
    private:
        Vec albedo;
        float fuzz;
};

#endif