#ifndef PLANEH
#define PLANEH

#include "basic_object.h"

class Plane: public BasicObject  {
    public:
        Plane(double _a, double _b, double _c, double _d, double _z, Material *_mat){
            a = _a;
            b = _b;
            c = _c;
            d = _d;
            z = _z;
            mat = _mat;
        }
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
    protected:
        Material *mat;
        double a,b,c,d,z;
};

// default hit implementation, overridden in childs
bool Plane::hit(const Ray &r, double tMin, double tMax, objectData &objData) const{
    return false; 
}

class PlaneXY: public virtual Plane {
    public:
        using Plane::Plane;
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
};

class PlaneYZ: public Plane {
    public:
        using Plane::Plane;
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
};

class PlaneXZ: public Plane {
    public:
        using Plane::Plane;
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
};

#endif