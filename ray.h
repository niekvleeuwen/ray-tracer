#ifndef RAY
#define RAY
#include "vector.cpp"

class Ray
{
    public:
        Ray();
        Ray(const Vec& _origin, const Vec& _direction);
        Vec getOrigin() const;
        Vec getDirection() const;
        Vec getPoint(double t) const;
    private:
        Vec origin;
        Vec direction;

};

#endif