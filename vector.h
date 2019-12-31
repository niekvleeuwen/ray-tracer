#ifndef VECTORH
#define VECTORH
#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec  {
    public:
        // Every vector has an X, Y and Z. Colors use this as (R, G, B)
        double x, y, z; 
        
        // Constructor of the Vector
        Vec(double x_=0, double y_=0, double z_=0) {
            x = x_;
            y = y_;
            z = z_;
        }

        double getX() { return x; }
        double getY() { return y; }
        double getZ() { return z; }

        double length();
        inline double squared_length() const { return x*x + y*y + z*z; }
        inline void normalise();
        Vec& operator-=(const Vec &a);

        void print();
};
#endif