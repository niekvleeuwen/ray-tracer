#include "camera.h"

// Setup camera
Camera::Camera(Vector3D cameraPosition, Vector3D CameraLookTo, double verticalFOV, double aspectWidthHeight) {
    float theta = verticalFOV*M_PI/180; // Field of view is top to bottom in degrees
    float half_height = tan(theta/2);
    float half_width = aspectWidthHeight * half_height;
    origin = cameraPosition;
    Vector3D w = unit_vector(cameraPosition - CameraLookTo);
    Vector3D u = unit_vector(cross(Vector3D(0,1,0), w));
    Vector3D v = cross(w, u);
    lower_left_corner = origin - half_width*u - half_height*v - w;
    horizontal = 2*half_width*u;
    vertical = 2*half_height*v;
}

Ray Camera::getRay(double u, double v) {
    return Ray(origin, lower_left_corner + horizontal*u + vertical*v - origin);
}