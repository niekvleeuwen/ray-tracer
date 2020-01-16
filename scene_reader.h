#ifndef SCENEREADERH
#define SCENEREADERH

#include <lib/json.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "cube.cpp"
#include "sphere.cpp"
#include "camera.cpp"
using json = nlohmann::json;

class SceneReader{
    public:
        SceneReader(int _widht, int _height);
        int parseJson();
        Scene *getScene();
    private:
        json scene;
        BasicObject **list;
        int pointer = 0;
        int width, height;
};

SceneReader::SceneReader(int _widht, int _height){
    width = _widht;
    height = _height;
}

int SceneReader::parseJson(){
    // read a file and parse to JSON
    std::cout << "Reading file..." <<std::endl;
    std::ifstream ifs("scene.json");
    try{
        scene = json::parse(ifs);
    }catch(std::exception&) {
        std::cout << "No file found or the file is not JSON formatted" << std::endl;
        exit(0);
    }
    return scene.size();
}

Scene *SceneReader::getScene(){
    this->parseJson();
    // give the array a size based on the number of objects in the scene
    list = new BasicObject*[scene.size() + 7];

    // define constant materials with different colors
    material *pink = new Diffuse(Vec(0.75, 0.25, 0.25));
    material *white = new Diffuse(Vec(0.73, 0.73, 0.73));
    material *blue = new Diffuse(Vec(0.25, 0.25, 0.75));
    material *light = new Light(Vec(7, 7, 7));

    // search for sphere key in the JSON
    try {
        auto& array = scene.at("sphere");
        //use a for loop for every sphere
        for (auto&& val: array) {
            std::string material = val.at("material");
            if(material == "diffuse"){
                list[pointer++] = new Sphere(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("radius"), blue);
            }else if(material == "reflective"){
                list[pointer++] = new Sphere(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("radius"), new Reflective(Vec(0.7, 0.6, 0.5)));
            }else{
                std::cout << material << " is not supported as a material." << std::endl;
            }
        }
    } catch(std::exception&) {
        std::cout << "No spheres found" << std::endl;
    }

    // search for cube key in the JSON
    try {
        auto& array = scene.at("cube");
        for (auto&& val: array) {
            std::string material = val.at("material");
            if(material == "diffuse"){
                list[pointer++] = new Cube(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("size"), pink);
            }else if(material == "reflective"){
                list[pointer++] = new Cube(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("size"), new Reflective(Vec(0.7, 0.6, 0.5)));
            }else{
                std::cout << material << " is not supported as a material." << std::endl;
            }
        }
    } catch(std::exception&) {
        std::cout << "No cubes found" << std::endl;
    }

    // init the camera object from the JSON object 
    auto& array = scene.at("camera");
    int fieldOfView = array.at("fov");
    auto&& lookFromPoint = array.at("lookFromPoint");
    auto&& lookToPoint = array.at("lookToPoint");
    Vec cameraPosition(lookFromPoint.at("x"), lookFromPoint.at("y"), lookFromPoint.at("z"));
    Vec cameraLookTo(lookToPoint.at("x"), lookToPoint.at("y"), lookToPoint.at("z"));
    Camera cam(cameraPosition, cameraLookTo, fieldOfView, double(width)/double(height));

    // ceiling
    list[pointer++] = new PlaneXZ(10, 40, 10, 40, 49, light);
    list[pointer++] = new flip_normals(new PlaneXZ(0, 50, 0, 50, 50, white));
    
    // left wall
    list[pointer++] = new flip_normals(new PlaneYZ(0, 50, 0, 50, 50, pink));

    // right wall
    list[pointer++] = new PlaneYZ(0, 50, 0, 50, 0, blue);
    // list[pointer++] = new PlaneYZ(100, 455, 100, 455, 0, light);

    // floor
    list[pointer++] = new PlaneXZ(0, 50, 0, 50, 0, white);

    // back wall
    list[pointer++] = new flip_normals(new PlaneXY(0, 50, 0, 50, 50, white));
    return new Scene(list,pointer, cam);
}

#endif