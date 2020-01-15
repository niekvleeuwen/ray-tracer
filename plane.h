#ifndef PLANEH
#define PLANEH

#include "basic_object.h"

class xy_plane: public BasicObject  {
    public:
        xy_plane() {}
        xy_plane(double _x0, double _x1, double _y0, double _y1, double _k, material *_mat){
            x0 = _x0;
            x1 = _x1;
            y0 = _y0; 
            y1 = _y1;
            k = _k;
            mat = _mat;
        }
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
    private:
        material *mat;
        double x0, x1, y0, y1, k;
};

class xz_plane: public BasicObject  {
    public:
        xz_plane() {}
        xz_plane(double _x0, double _x1, double _z0, double _z1, double _k, material *_mat){
            x0 = _x0;
            x1 = _x1;
            z0 = _z0; 
            z1 = _z1;
            k = _k;
            mat = _mat;
        }
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
    private:
        material *mat;
        double x0, x1, z0, z1, k;
};

class yz_plane: public BasicObject  {
    public:
        yz_plane() {}
        yz_plane(double _y0, double _y1, double _z0, double _z1, double _k, material *_mat){
            y0 = _y0;
            y1 = _y1; 
            z0 = _z0;
            z1 = _z1;
            k = _k;
            mat = _mat;
        }
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
    private:
        material *mat;
        double y0, y1, z0, z1, k;
};

bool xy_plane::hit(const Ray& r, double t0, double t1, hit_record& rec) const {
    double t = (k-r.getOrigin().z) / r.getDirection().z;
    if (t < t0 || t > t1)
        return false;
    double x = r.getOrigin().x + t*r.getDirection().x;
    double y = r.getOrigin().y + t*r.getDirection().y;
    if (x < x0 || x > x1 || y < y0 || y > y1) 
        return false;
    rec.u = (x-x0)/(x1-x0);
    rec.v = (y-y0)/(y1-y0); 
    rec.t = t;
    rec.mat_ptr = mat;
    rec.p = r.getPoint(t);
    rec.normal = Vec(0, 0, 1);
    return true;
}

bool xz_plane::hit(const Ray& r, double t0, double t1, hit_record& rec) const {
    double t = (k-r.getOrigin().y) / r.getDirection().y;
    if (t < t0 || t > t1)
        return false;
    double x = r.getOrigin().x + t*r.getDirection().x;
    double z = r.getOrigin().z + t*r.getDirection().z;
    if (x < x0 || x > x1 || z < z0 || z > z1) 
        return false;
    rec.u = (x-x0)/(x1-x0);
    rec.v = (z-z0)/(z1-z0); 
    rec.t = t;
    rec.mat_ptr = mat;
    rec.p = r.getPoint(t);
    rec.normal = Vec(0, 1, 0);
    return true;
}

bool yz_plane::hit(const Ray& r, double t0, double t1, hit_record& rec) const {
    double t = (k-r.getOrigin().x) / r.getDirection().x;
    if (t < t0 || t > t1)
        return false;
    double y = r.getOrigin().y + t*r.getDirection().y;
    double z = r.getOrigin().z + t*r.getDirection().z;
    if (y < y0 || y > y1 || z < z0 || z > z1) 
        return false;
    rec.u = (y-y0)/(y1-y0);
    rec.v = (z-z0)/(z1-z0); 
    rec.t = t;
    rec.mat_ptr = mat;
    rec.p = r.getPoint(t);
    rec.normal = Vec(1, 0, 0);
    return true;
}

#endif