#ifndef SPHEREH
#define SPHEREH

#include "basic_object.h"

class Sphere: public BasicObject {
    public:
        Sphere(Vec _center, double _radius, material *_mat);
        virtual bool hit(const Ray& ray, double tmin, double tmax, objectData& rec) const;
    private:
        Vec center;
        double radius;
        material* mat;
};

#endif