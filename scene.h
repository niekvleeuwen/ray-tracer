#ifndef SCENEH
#define SCENEH

#include "basic_object.h"
#include "materials.h"
#include "camera.h"

class Scene: public BasicObject  {
    public:
        Scene() {}
        Scene(BasicObject **_list, int _listSize);
        void setCamera(Camera *_cam);
        Vec trace(const Ray &r, int depth);
        Vec getColor(double x, double y);
        virtual bool hit(const Ray &r, double tmin, double tmax, objectData &objData) const;
    private:
        Camera* cam;
        BasicObject **list;
        int listSize;
};

#endif
