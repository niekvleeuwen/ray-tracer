#ifndef BASIC_OBJECTH
#define BASIC_OBJECTH

#include "ray.h"

class material; //Alert the compiler that the pointer currentMaterial is to a class

struct hit_record{
    double t;  
    double u;
    double v;
    Vec p;
    Vec normal;
    material *currentMaterial;
};

class BasicObject {
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

class flip_normals : public BasicObject {
    public:
        flip_normals(BasicObject *p) : ptr(p) {}

        virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_record& rec) const {

            if (ptr->hit(r, t_min, t_max, rec)) {
                rec.normal -= rec.normal;
                return true;
            }
            else
                return false;
        }
        BasicObject *ptr;
};


#endif