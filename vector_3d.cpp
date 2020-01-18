#include "vector_3d.h"

double Vector3D::getX(){ 
    return x;
}

double Vector3D::getY(){ 
    return y; 
    }
double Vector3D::getZ(){ 
    return z; 
}

// Calculate the length
double Vector3D::length() const {
    return sqrt(x*x + y*y + z*z);
}

// Return the length without doing taking the square root
inline double Vector3D::notSquaredLength() const { 
    return x*x + y*y + z*z; 
}

// Normalise the vector
Vector3D Vector3D::normalise() const {
    double l = sqrt(x*x + y*y + z*z);
    return Vector3D(x/l, y/l, z/l);
}


// Print the fields
void Vector3D::print(){
    std::cout << "("<< x << "," << y << "," << z << ")" << std::endl;
}

// Substract the vectors with another Vector3Dtor
Vector3D &Vector3D::operator-=(const Vector3D& a) {
    x -= x;
    y -= y;
    z -= z;
    return *this;
}

// Add the vectors together to a new one
Vector3D operator+(const Vector3D &a, const Vector3D &b) {
    return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Substract the vectors from each other
Vector3D operator-(const Vector3D &a, const Vector3D &b) {
    return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Multiply the vector with another Vector3Dtor
Vector3D operator*(const Vector3D &a, const Vector3D &b) {
    return Vector3D(a.x * b.x, a.y * b.y, a.z * b.z);
}

// Multiply the vector with a double
Vector3D operator*(double t, const Vector3D &v) {
    return Vector3D(t*v.x, t*v.y, t*v.z);
}
Vector3D operator*(const Vector3D &v, double t) {
    return Vector3D(t*v.x, t*v.y, t*v.z);
}

// Divide the vector with another Vector3Dtor
Vector3D operator/(const Vector3D &a, const Vector3D &b) {
    return Vector3D(a.x / b.x, a.y / b.y, a.z / b.z);
}

// Divide the vector with a double
Vector3D operator/(Vector3D v, double t) {
    return Vector3D(v.x/t, v.y/t, v.z/t);
}

// Dot product of two vectors
inline double dot(const Vector3D &a, const Vector3D &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product of vectors
inline Vector3D cross(const Vector3D &a, const Vector3D &b) {
    return Vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// Return the unit vector
inline Vector3D unit_vector(Vector3D v) {
    return v / v.length();
}

