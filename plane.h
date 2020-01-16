#ifndef PLANEH
#define PLANEH

#include "basic_object.h"

// class Plane: public BasicObject  {
//     public:
//         Plane(double _a, double _b, double _c, double _d, double _k, material *_mat){
//             a = _a;
//             b = _b;
//             c = _c;
//             d = _d;
//             k = _k;
//             mat = _mat;
//         }
//         virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
//     private:
//         material *mat;
//         double a,b,c,d,k;
// };

class xy_plane: public BasicObject {
    public:
        xy_plane(double _a, double _b, double _c, double _d, double _k, material *_mat){
            a = _a;
            b = _b;
            c = _c;
            d = _d;
            k = _k;
            mat = _mat;
        }
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
    private:
        material *mat;
        double a,b,c,d,k;
};

class yz_plane: public BasicObject {
    public:
        yz_plane(double _a, double _b, double _c, double _d, double _k, material *_mat){
            a = _a;
            b = _b;
            c = _c;
            d = _d;
            k = _k;
            mat = _mat;
        }
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
    private:
        material *mat;
        double a,b,c,d,k;
};

class xz_plane: public BasicObject {
    public:
        xz_plane(double _a, double _b, double _c, double _d, double _k, material *_mat){
            a = _a;
            b = _b;
            c = _c;
            d = _d;
            k = _k;
            mat = _mat;
        }
        virtual bool hit(const Ray& r, double t0, double t1, hit_record& rec) const;
    private:
        material *mat;
        double a,b,c,d,k;
};


bool xy_plane::hit(const Ray& r, double t0, double t1, hit_record& rec) const {
    double t = (k-r.getOrigin().z) / r.getDirection().z;
    if (t < t0 || t > t1)
        return false;
    double x = r.getOrigin().x + t*r.getDirection().x;
    double y = r.getOrigin().y + t*r.getDirection().y;
    if (x < a || x > b || y < c || y > d) 
        return false;
    rec.u = (x-a)/(b-a);
    rec.v = (y-c)/(d-c); 
    rec.t = t;
    rec.currentMaterial = mat;
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
    if (x < a || x > b || z < c || z > d) 
        return false;
    rec.u = (x-a)/(b-a);
    rec.v = (z-c)/(d-c); 
    rec.t = t;
    rec.currentMaterial = mat;
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
    if (y < a || y > b || z < c || z > d){
        return false;
    } else{
        rec.u = (y-a)/(b-a);
        rec.v = (z-c)/(d-c); 
        rec.t = t;
        rec.currentMaterial = mat;
        rec.p = r.getPoint(t);
        rec.normal = Vec(1, 0, 0);
    }
    return true;
}

#endif