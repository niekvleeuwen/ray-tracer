#ifndef CUBEH
#define CUBEH

#include "plane.h"
#include "scene.h"

class Cube: public BasicObject  {
    public:
        Cube(Vec _center, double _size, Material *_material);
        ~Cube();
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
    private:
        Vec center;
        double size;
        BasicObject *cubeObjects;
};

#endif