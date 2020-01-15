#ifndef RENDERERH
#define RENDERERH

#include "basic_object.h"

class Renderer {
    public:
        Renderer(int _width, int _height, int _sampelsPerPixel, std::string _filePath);
        void updateProgressBar(int rowsDone);
        bool render();
    private:
        int width; 
        int height;
        int sampelsPerPixel;
        std::string filePath;
};

#endif