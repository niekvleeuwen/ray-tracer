#ifndef CUBEH
#define CUBEH

#include "plane.h"
#include "scene.h"

class Cube: public BasicObject  {
    public:
        Cube() {}
        Cube(const Vec& center, double size, material *ptr);
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
    private:
        Vec center;
        double size;
        BasicObject *list_ptr;
};

#endif