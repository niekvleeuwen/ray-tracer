#ifndef CUBEH
#define CUBEH

#include "rect.h"
#include "hitable_list.h"

class Cube: public BasicObject  {
    public:
        Vec center;
        double size;
        BasicObject *list_ptr;
        Cube() {}
        Cube(const Vec& center, double size, material *ptr);
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
};

#endif