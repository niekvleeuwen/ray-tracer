#ifndef BASIC_OBJECTH
#define BASIC_OBJECTH

#include "ray.h"

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
class flippedBasicObject : public BasicObject {
    public:
        flippedBasicObject(BasicObject *_basicObject){
            basicObject = _basicObject;
        }
        ~flippedBasicObject(){
            delete basicObject;
        }
        virtual bool hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
            if (basicObject->hit(r, tMin, tMax, objData)){
                objData.normal -= objData.normal;
                return true;
            }
            return false;
        }
    private:
        BasicObject *basicObject;
};


#endif