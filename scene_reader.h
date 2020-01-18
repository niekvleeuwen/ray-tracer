#ifndef SCENEREADERH
#define SCENEREADERH

#include <lib/json.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "cube.cpp"
#include "sphere.cpp"
#include "planes.cpp"
#include "camera.cpp"
#include "flipped_basic_object.cpp"
#include "light.cpp"
#include "diffuse.cpp"
#include "reflective.cpp"

using json = nlohmann::json;

class SceneReader{
    public:
        SceneReader(int _widht, int _height, std::string _scenePath);
        int parseJson();
        RayTracer *getScene();
    private:
        json scene;
        BasicObject **list;
        int pointer = 0;
        int width, height;
        std::string scenePath;
};

#endif