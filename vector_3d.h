#ifndef VECTORH
#define VECTORH
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

class Vector3D {
    public:
        // Every vector has an X, Y and Z. Colors use this as (R, G, B)
        double x, y, z; 
        
        // Constructor of the Vector
        Vector3D(double x_=0, double y_=0, double z_=0) {
            x = x_;
            y = y_;
            z = z_;
        }

        double getX();
        double getY();
        double getZ();
        double length() const;
        inline double notSquaredLength() const;
        Vector3D normalise() const;
        void print();
        Vector3D& operator-=(const Vector3D &a);
};
#endif