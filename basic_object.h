#ifndef BASIC_OBJECTH
#define BASIC_OBJECTH

#include "ray.cpp"

class Material; // Alert the compiler that the pointer currentMaterial is to a class

// This struct is used to prevent the use of 6 paramaters in every function
struct objectData{
    double t;  
    double u;
    double v;
    Vector3D p;
    Vector3D normal;
    Material *currentMaterial;
};

class BasicObject {
    public:
        virtual ~BasicObject(){}; // Implemented in childs
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const = 0;
};

// This class holds another BasicObject and reverses the normals
class FlippedBasicObject : public BasicObject {
    public:
        FlippedBasicObject(BasicObject *_basicObject);
        ~FlippedBasicObject();
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
    private:
        BasicObject *basicObject;
};

class Sphere: public BasicObject {
    public:
        Sphere(Vector3D _center, double _radius, Material *_material);
        ~Sphere();
        virtual bool hit(const Ray &ray, double tMin, double tMax, objectData &objData) const;
    private:
        Vector3D center;
        double radius;
        Material *material;
};

class Cube: public BasicObject  {
    public:
        Cube(Vector3D _center, double _size, Vector3D _material);
        ~Cube();
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
    private:
        Vector3D center;
        double size;
        BasicObject *cubeObjects;
};

class Plane: public BasicObject  {
    public:
        Plane(double _a, double _b, double _c, double _d, double _z, Material *_material);
        virtual ~Plane(){}; // Implemented in childs
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
    protected:
        Material *material;
        double a,b,c,d,z;
};

class PlaneXY: public Plane {
    public:
        using Plane::Plane;
        ~PlaneXY();
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
};

class PlaneYZ: public Plane {
    public:
        using Plane::Plane;
        ~PlaneYZ();
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
};

class PlaneXZ: public Plane {
    public:
        using Plane::Plane;
        ~PlaneXZ();
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const;
};

#endif