#ifndef CUBEH
#define CUBEH

#include "rect.h"
#include "hitable_list.h"

class Cube: public BasicObject  {
    public:
        Vec pmin, pmax;
        BasicObject *list_ptr;
        Cube() {}
        Cube(const Vec& p0, const Vec& p1, material *ptr);
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
};

#endif