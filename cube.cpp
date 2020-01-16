#include "cube.h"

Cube::Cube(const Vec& _center, double _size, material *ptr) {
    center = _center;
    size = _size;
    BasicObject **list = new BasicObject*[6];

    int xMin = center.x - size;
    int yMin = center.y - size;
    int zMin = center.z - size;
    int xPlus = center.x + size;
    int yPlus = center.y + size;
    int zPlus = center.z + size;

    list[0] = new PlaneXY(xMin, xPlus, yMin, yPlus, zPlus, ptr);
    list[1] = new flip_normals(new PlaneXY(xMin, xPlus, yMin, yPlus, zMin, ptr));
    list[2] = new PlaneXZ(xMin, xPlus, zMin, zPlus, yPlus, ptr);
    list[3] = new flip_normals(new PlaneXZ(xMin, xPlus, zMin, zPlus, yMin, ptr));
    list[4] = new PlaneYZ(yMin, yPlus, zMin, zPlus, xPlus, ptr);
    list[5] = new flip_normals(new PlaneYZ(yMin, yPlus, zMin, zPlus, xMin, ptr));
    list_ptr = new Scene(list,6, Camera()); //fix the empty camera
}

bool Cube::hit(const Ray& r, double t0, double t1, objectData& rec) const {
    return list_ptr->hit(r, t0, t1, rec);
}
