#include "vector.h"

// Calculate the length
double Vec::length() const {
    return sqrt(x*x + y*y + z*z);
}

// Normalise the vector
Vec Vec::normalise() const {
    double l = sqrt(x*x + y*y + z*z);
    return Vec(x/l, y/l, z/l);
}

void Vec::print(){
    printf("(%f,%f,%f)\n",x,y,z);
}

Vec &Vec::operator-=(const Vec& a) {
    x -= x;
    y -= y;
    z -= z;
    return *this;
}

// Add the vectors together to a new one
Vec operator+(const Vec &a, const Vec &b) {
    return Vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Substract the vectors from each other
Vec operator-(const Vec &a, const Vec &b) {
    return Vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Multiply the vector with another vector
Vec operator*(const Vec &a, const Vec &b) {
    return Vec(a.x * b.x, a.y * b.y, a.z * b.z);
}

// Multiply the vector with a double
Vec operator*(double t, const Vec &v) {
    return Vec(t*v.x, t*v.y, t*v.z);
}
Vec operator*(const Vec &v, double t) {
    return Vec(t*v.x, t*v.y, t*v.z);
}

// Divide the vector with another vector
Vec operator/(const Vec &a, const Vec &b) {
    return Vec(a.x / b.x, a.y / b.y, a.z / b.z);
}

// Divide the vector with a double
Vec operator/(Vec v, double t) {
    return Vec(v.x/t, v.y/t, v.z/t);
}

// Dot product of two vectors
inline double dot(const Vec &a, const Vec &b) {
    return a.x * b.x
         + a.y * b.y
         + a.z * b.z;
}

// Cross product of vectors
inline Vec cross(const Vec &a, const Vec &b) {
    return Vec(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

// Return the unit vector
inline Vec unit_vector(Vec v) {
    return v / v.length();
}
