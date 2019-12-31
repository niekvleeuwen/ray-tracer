#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class Camera {
    public:
        Vec origin;
        Vec lower_left_corner;
        Vec horizontal;
        Vec vertical;

        // set up camera
        Camera(Vec cameraPosition, Vec CameraLookTo, Vec verticalUp, double verticalFOV, double aspect);
        Ray get_ray(double u, double v);
};

#endif