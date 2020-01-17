#ifndef MATERIALH
#define MATERIALH

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
        Diffuse(Vec _color);
        Vec random_in_unit_sphere() const;
        double randomDouble() const;
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vec &attenuation, Ray &scattered) const;
    private:
        Vec color;
};

class Light : public Material {
    public:
        Light(Vec _emitColor);
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vec &attenuation, Ray &scattered) const;
        virtual Vec emitted(float u, float v, const Vec& p) const;
    private:
        Vec emitColor;
};

class Reflective : public Material {
    public:
        Reflective(const Vec &a);
        Vec reflect(const Vec &v, const Vec &n) const;
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vec &attenuation, Ray &scattered) const;
    private:
        Vec albedo;
};

#endif