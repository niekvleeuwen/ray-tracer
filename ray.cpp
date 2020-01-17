#include "ray.h"

Ray::Ray(){}
Ray::Ray(const Vec& _origin, const Vec& _direction){ 
    origin = _origin; 
    direction= _direction; 
}

// Get methods
Vec Ray::getOrigin() const { 
    return origin; 
}
Vec Ray::getDirection() const    { 
    return direction; 
}

// Returns the vector at the point t
Vec Ray::getPoint(double t) const { 
    return origin + direction*t; 
}