#ifndef HITABLELISTH
#define HITABLELISTH

#include "basic_object.h"

class hitable_list: public BasicObject  {
    public:
        hitable_list() {}
        hitable_list(BasicObject **l, int n) { list = l; list_size = n; }
        virtual bool hit(const Ray& r, double tmin, double tmax, hit_record& rec) const;
        BasicObject **list;
        int list_size;
};

bool hitable_list::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}


#endif
