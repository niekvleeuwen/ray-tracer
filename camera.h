#ifndef CAMERAH
#define CAMERAH

class Camera {
    public:
        Camera(){}
        Camera(Vector3D cameraPosition, Vector3D CameraLookTo, double verticalFOV, double ratioWidthHeight);
        Ray getRay(double x, double y);
    private:
        Vector3D origin;
        Vector3D lower_left_corner;
        Vector3D horizontal;
        Vector3D vertical;
};

#endif