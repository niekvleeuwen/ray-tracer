#ifndef CUBEH
#define CUBEH

#include "plane.h"
#include "scene.h"

class Cube: public BasicObject  {
    public:
        Cube(const Vec& center, double size, Material *ptr);
        virtual bool hit(const Ray& r, double t0, double t1, objectData& rec) const;
    private:
        Vec center;
        double size;
        BasicObject *list_ptr;
};

#endif