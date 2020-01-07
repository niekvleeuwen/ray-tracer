#ifndef TEXTUREH
#define TEXTUREH

#include "vector.h"

class texture {
    public:
        virtual Vec value(float u, float v, const Vec& p) const = 0;
};

class constant_texture : public texture {
    public:
        constant_texture() {}
        constant_texture(Vec c) : color(c) {}
        virtual Vec value(float u, float v, const Vec& p) const {
            return color;
        }
        Vec color;
};

class checker_texture : public texture {
    public:
        checker_texture() { }
        checker_texture(texture *t0, texture *t1){
            even = t0;
            odd = t1;
        }
        virtual Vec value(float u, float v, const Vec& p) const {
            float sines = sin(10*p.x)*sin(10*p.y)*sin(10*p.z);
            if (sines < 0)
                return odd->value(u, v, p);
            else
                return even->value(u, v, p);
        }
    private:
        texture *odd;
        texture *even;

};

#endif