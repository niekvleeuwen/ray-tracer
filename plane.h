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


bool PlaneXY::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    double t = (z-r.getOrigin().z) / r.getDirection().z;
    if (t < tMin || t > tMax)
        return false;
    double x = r.getOrigin().x + t*r.getDirection().x;
    double y = r.getOrigin().y + t*r.getDirection().y;
    if (x < a || x > b || y < c || y > d) 
        return false;
    objData.u = (x-a)/(b-a);
    objData.v = (y-c)/(d-c); 
    objData.t = t;
    objData.currentMaterial = mat;
    objData.p = r.getPoint(t);
    objData.normal = Vec(0, 0, 1);
    return true;
}

bool PlaneXZ::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    double t = (z-r.getOrigin().y) / r.getDirection().y;
    if (t < tMin || t > tMax)
        return false;
    double x = r.getOrigin().x + t*r.getDirection().x;
    double z = r.getOrigin().z + t*r.getDirection().z;
    if (x < a || x > b || z < c || z > d) 
        return false;
    objData.u = (x-a)/(b-a);
    objData.v = (z-c)/(d-c); 
    objData.t = t;
    objData.currentMaterial = mat;
    objData.p = r.getPoint(t);
    objData.normal = Vec(0, 1, 0);
    return true;
}

bool PlaneYZ::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    double t = (z-r.getOrigin().x) / r.getDirection().x;
    if (t < tMin || t > tMax)
        return false;
    double y = r.getOrigin().y + t*r.getDirection().y;
    double z = r.getOrigin().z + t*r.getDirection().z;
    if (y < a || y > b || z < c || z > d){
        return false;
    } else{
        objData.u = (y-a)/(b-a);
        objData.v = (z-c)/(d-c); 
        objData.t = t;
        objData.currentMaterial = mat;
        objData.p = r.getPoint(t);
        objData.normal = Vec(1, 0, 0);
    }
    return true;
}

#endif