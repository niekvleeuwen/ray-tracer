#ifndef RAYH
#define RAYH

#include "vector.cpp"

class Ray
{
    public:
        Ray() {}
        Ray(const Vec& a, const Vec& b) { A = a; B = b; }
        Vec origin() const       { return A; }
        Vec direction() const    { return B; }
        Vec point_at_parameter(double t) const { return A + t*B; }

        Vec A;
        Vec B;
};

#endif
