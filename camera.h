#ifndef CAMERAH
#define CAMERAH

class Camera {
    public:
        Camera(){}
        Camera(Vec cameraPosition, Vec CameraLookTo, double verticalFOV, double aspectWidthHeight);
        Ray getRay(double u, double v);
    private:
        Vec origin;
        Vec lower_left_corner;
        Vec horizontal;
        Vec vertical;
};

#endif