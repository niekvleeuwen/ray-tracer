#ifndef RAY
#define RAY
#include "vector_3d.cpp"

class Ray
{
    public:
        Ray();
        Ray(const Vector3D& _origin, const Vector3D& _direction);
        Vector3D getOrigin() const;
        Vector3D getDirection() const;
        Vector3D getPoint(double t) const;
    private:
        Vector3D origin;
        Vector3D direction;

};

#endif