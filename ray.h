#ifndef RAY
#define RAY
#include "vector.cpp"

class Ray
{
    public:
        Vec origin;
        Vec direction;

        // Constructor of the ray
        Ray(){}
        Ray(const Vec& _origin, const Vec& _direction){ 
            origin = _origin; 
            direction= _direction; 
        }

        // Get methods
        Vec getOrigin() const { 
            return origin; 
        }
        Vec getDirection() const    { 
            return direction; 
        }

        // Returns the vector at point 
        Vec getPoint(double t) const { 
            return origin + direction*t; 
        }
};

#endif