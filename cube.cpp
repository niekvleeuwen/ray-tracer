#include "basic_object.h"

Cube::Cube(Vector3D _center, double _size, Vector3D _material){
    center = _center;
    size = _size;
    BasicObject **list = new BasicObject*[6];
    
    // Define the corner points of the cube
    int xMin = center.getX() - size;
    int yMin = center.getY() - size;
    int zMin = center.getZ() - size;
    int xPlus = center.getX() + size;
    int yPlus = center.getY() + size;
    int zPlus = center.getZ() + size;

    // The cube consists out of 6 planes stored in a scene
    list[0] = new PlaneXY(xMin, xPlus, yMin, yPlus, zPlus, new Diffuse(_material));
    list[1] = new FlippedBasicObject(new PlaneXY(xMin, xPlus, yMin, yPlus, zMin, new Diffuse(_material)));
    list[2] = new PlaneXZ(xMin, xPlus, zMin, zPlus, yPlus, new Diffuse(_material));
    list[3] = new FlippedBasicObject(new PlaneXZ(xMin, xPlus, zMin, zPlus, yMin, new Diffuse(_material)));
    list[4] = new PlaneYZ(yMin, yPlus, zMin, zPlus, xPlus, new Diffuse(_material));
    list[5] = new FlippedBasicObject(new PlaneYZ(yMin, yPlus, zMin, zPlus, xMin, new Diffuse(_material)));
    cubeObjects = new RayTracer(list,6);
}

Cube::~Cube(){
    delete cubeObjects;
}

bool Cube::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    return cubeObjects->hit(r, tMin, tMax, objData);
}
