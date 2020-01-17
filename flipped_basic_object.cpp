#include "basic_object.h"

FlippedBasicObject::FlippedBasicObject(BasicObject *_basicObject){
    basicObject = _basicObject;
}

FlippedBasicObject::~FlippedBasicObject(){
    delete basicObject;
}

bool FlippedBasicObject::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    if (basicObject->hit(r, tMin, tMax, objData)){
        objData.normal -= objData.normal; // reverse the normal
        return true;
    }
    return false;
}