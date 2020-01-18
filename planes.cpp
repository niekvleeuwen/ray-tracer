#include "planes.h"

bool PlaneXY::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    double t = (z-r.getOrigin().getZ()) / r.getDirection().getZ();
    if (t < tMin || t > tMax)
        return false;
    double x = r.getOrigin().getX() + t*r.getDirection().getX();
    double y = r.getOrigin().getY() + t*r.getDirection().getY();
    if (x < a || x > b || y < c || y > d) 
        return false;
    objData.u = (x-a)/(b-a);
    objData.v = (y-c)/(d-c); 
    objData.t = t;
    objData.currentMaterial = mat;
    objData.p = r.getPoint(t);
    objData.normal = Vector3D(0, 0, 1);
    return true;
}

bool PlaneXZ::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    double t = (z-r.getOrigin().getY()) / r.getDirection().getY();
    if (t < tMin || t > tMax)
        return false;
    double x = r.getOrigin().getX() + t*r.getDirection().getX();
    double z = r.getOrigin().getZ() + t*r.getDirection().getZ();
    if (x < a || x > b || z < c || z > d) 
        return false;
    objData.u = (x-a)/(b-a);
    objData.v = (z-c)/(d-c); 
    objData.t = t;
    objData.currentMaterial = mat;
    objData.p = r.getPoint(t);
    objData.normal = Vector3D(0, 1, 0);
    return true;
}

bool PlaneYZ::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    double t = (z-r.getOrigin().getX()) / r.getDirection().getX();
    if (t < tMin || t > tMax)
        return false;
    double y = r.getOrigin().getY() + t*r.getDirection().getY();
    double z = r.getOrigin().getZ() + t*r.getDirection().getZ();
    if (y < a || y > b || z < c || z > d){
        return false;
    } else{
        objData.u = (y-a)/(b-a);
        objData.v = (z-c)/(d-c); 
        objData.t = t;
        objData.currentMaterial = mat;
        objData.p = r.getPoint(t);
        objData.normal = Vector3D(1, 0, 0);
    }
    return true;
}