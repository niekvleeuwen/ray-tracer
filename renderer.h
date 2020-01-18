#ifndef RENDERERH
#define RENDERERH

#include "basic_object.h"
#include <fstream>

class Renderer {
    public:
        Renderer(int _width, int _height, int _sampelsPerPixel, std::string _filePath);
        void initFile();
        bool renderScene(RayTracer *_scene);
        void writeColorToFile(Vector3D color);
        void updateProgressBar(int rowsDone);
    private:
        int width; 
        int height;
        int sampelsPerPixel;
        std::string filePath;
        std::ofstream img;
};

#endif