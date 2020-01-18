#include "materials.h"

Vector3D Material::emitted(float u, float v, const Vector3D& p) const {
    return Vector3D(0,0,0); // On default return black (for non emitting objects)
}