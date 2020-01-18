#ifndef CAMERAH
#define CAMERAH

class Camera {
    public:
        Camera(){}
        Camera(Vector3D cameraPosition, Vector3D CameraLookTo, double verticalFOV, double aspectWidthHeight);
        Ray getRay(double u, double v);
    private:
        Vector3D origin;
        Vector3D lower_left_corner;
        Vector3D horizontal;
        Vector3D vertical;
};

#endif