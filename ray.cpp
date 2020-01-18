#include "ray.h"

Ray::Ray(){}
Ray::Ray(const Vector3D& _origin, const Vector3D& _direction){ 
    origin = _origin; 
    direction= _direction; 
}

// Get methods
Vector3D Ray::getOrigin() const { 
    return origin; 
}
Vector3D Ray::getDirection() const    { 
    return direction; 
}

// Returns the Vector3Dtor at the point t
Vector3D Ray::getPoint(double t) const { 
    return origin + direction*t; 
}