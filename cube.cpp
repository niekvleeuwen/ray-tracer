#include "cube.h"

Cube::Cube(Vec _center, double _size, Material *_material){
    center = _center;
    size = _size;
    BasicObject **list = new BasicObject*[6];
    
    // Define the corner points of the cube
    int xMin = center.x - size;
    int yMin = center.y - size;
    int zMin = center.z - size;
    int xPlus = center.x + size;
    int yPlus = center.y + size;
    int zPlus = center.z + size;

    // The cube consists out of 6 planes stored in a scene
    list[0] = new PlaneXY(xMin, xPlus, yMin, yPlus, zPlus, _material);
    list[1] = new flippedBasicObject(new PlaneXY(xMin, xPlus, yMin, yPlus, zMin, _material));
    list[2] = new PlaneXZ(xMin, xPlus, zMin, zPlus, yPlus, _material);
    list[3] = new flippedBasicObject(new PlaneXZ(xMin, xPlus, zMin, zPlus, yMin, _material));
    list[4] = new PlaneYZ(yMin, yPlus, zMin, zPlus, xPlus, _material);
    list[5] = new flippedBasicObject(new PlaneYZ(yMin, yPlus, zMin, zPlus, xMin, _material));
    cubeObjects = new Scene(list,6);
}

Cube::~Cube(){
    //delete cubeObjects;
    std::cout << "deleted" << std::endl;
}

bool Cube::hit(const Ray &r, double tMin, double tMax, objectData &objData) const {
    return cubeObjects->hit(r, tMin, tMax, objData);
}
