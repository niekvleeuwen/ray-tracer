#include "camera.h"

// setup camera
Camera::Camera(Vec cameraPosition, Vec CameraLookTo, double verticalFOV, double aspect) {
    // vfov is top to bottom in degrees
    Vec u, v, w; //defined in the figure 11-3
    float theta = verticalFOV*M_PI/180;
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    origin = cameraPosition;
    w = unit_vector(cameraPosition - CameraLookTo);
    u = unit_vector(cross(Vec(0,1,0), w));
    v = cross(w, u);
    lower_left_corner = origin - half_width*u - half_height*v - w;
    horizontal = 2*half_width*u;
    vertical = 2*half_height*v;
}

Ray Camera::get_ray(double u, double v) {
    return Ray(origin, lower_left_corner + horizontal*u + vertical*v - origin);
}