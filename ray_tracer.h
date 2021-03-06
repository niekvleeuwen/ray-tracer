#ifndef RAYTRACERH
#define RAYTRACERH

#include "basic_object.h"
#include "camera.h"
#include "materials.cpp"

class RayTracer: public BasicObject  {
    public:
        RayTracer(BasicObject **_list, int _listSize);
        ~RayTracer();
        void setCamera(Camera *_cam);
        Vector3D trace(const Ray &r, int depth);
        Vector3D getColor(double x, double y);
        virtual bool hit(const Ray &r, double tmin, double tmax, objectData &objData) const;
    private:
        Camera *cam = nullptr;
        BasicObject **list;
        int listSize;
};

#endif
