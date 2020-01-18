#ifndef MATERIALH
#define MATERIALH

#include "basic_object.h"

struct objectData;

class Material  {
    public:
        virtual ~Material(){}
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vector3D& attenuation, Ray& scattered) const = 0;
        virtual Vector3D emitted(float u, float v, const Vector3D& p) const {
            return Vector3D(0,0,0); // On default return black (for non emitting objects)
        }
};

class Diffuse : public Material {
    public:
        Diffuse(Vector3D _color);
        Vector3D random_in_unit_sphere() const;
        double randomDouble() const;
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vector3D &attenuation, Ray &scattered) const;
    private:
        Vector3D color;
};

class Light : public Material {
    public:
        Light(Vector3D _emitColor);
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vector3D &attenuation, Ray &scattered) const;
        virtual Vector3D emitted(float u, float v, const Vector3D& p) const;
    private:
        Vector3D emitColor;
};

class Reflective : public Material {
    public:
        Reflective(const Vector3D &_albedo);
        Vector3D reflect(const Vector3D &v, const Vector3D &n) const;
        virtual bool scatter(const Ray &r_in, const objectData &objData, Vector3D &attenuation, Ray &scattered) const;
    private:
        Vector3D albedo;
};

#endif