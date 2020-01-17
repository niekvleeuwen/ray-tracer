#ifndef BASIC_OBJECTH
#define BASIC_OBJECTH

#include "ray.cpp"

class Material; // Alert the compiler that the pointer currentMaterial is to a class

// This struct is used to prevent the use of 6 paramaters in every function
struct objectData{
    double t;  
    double u;
    double v;
    Vec p;
    Vec normal;
    Material *currentMaterial;
};

class BasicObject {
    public:
        virtual ~BasicObject(){};
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
        Sphere(Vec _center, double _radius, Material *_mat);
        ~Sphere(){}
        virtual bool hit(const Ray &ray, double tMin, double tMax, objectData &objData) const;
    private:
        Vec center;
        double radius;
        Material* mat;
};

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