#ifndef SPHEREH
#define SPHEREH

#include "basic_object.h"

class Sphere: public BasicObject {
    public:
        Sphere(Vec _center, double _radius, Material *_mat);
        ~Sphere(){}
        virtual bool hit(const Ray &ray, double tMin, double tMax, objectData &objData) const;
    private:
        Vec center;
        double radius;
        Material* mat;
};

#endif