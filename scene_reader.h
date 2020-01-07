#ifndef SCENEREADERH
#define SCENEREADERH

#include <lib/json.hpp>
#include <vector>
#include <fstream>
#include <iostream>
using json = nlohmann::json;

class SceneReader{
    public:
        SceneReader();
        int parseJson();
        bool convertJSONtoScene();
        hitable_list *getScene();
    private:
        json scene;
        BasicObject **list;
        int pointer = 0;
};

SceneReader::SceneReader(){
    int size = this->parseJson();
    // give the array a size based on the number of objects in the scene
    list = new BasicObject*[size + 7];
    this->convertJSONtoScene();
}

int SceneReader::parseJson(){
    // read a file and parse to JSON
    std::cout << "Reading file.." <<std::endl;
    std::ifstream ifs("scene.json");
    try{
        scene = json::parse(ifs);
    }catch(std::exception&) {
        std::cout << "No file found or the file is not JSON formatted" << std::endl;
        exit(0);
    }
    return scene.size();
}

bool SceneReader::convertJSONtoScene(){
    // read a file and parse to JSON
    std::cout << "Parsing json.." <<std::endl;
    std::ifstream ifs("scene.json");
    scene = json::parse(ifs);

    // search for sphere key in the JSON
    try {
        auto& array = scene.at("sphere");
        //use a for loop for every sphere
        for (auto&& val: array) {
            std::string material = val.at("material");
            if(material == "diffuse"){
                list[pointer++] = new sphere(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("radius"), new diffuse(Vec(0.7,0.3,0.3)));
            }else if(material == "metal"){
                list[pointer++] = new sphere(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("radius"), new metal(Vec(0.7, 0.6, 0.5), 0));
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
                list[pointer++] = new Cube(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("size"), new diffuse(Vec(0.7,0.3,0.3)));
            }else if(material == "metal"){
                list[pointer++] = new Cube(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("size"), new metal(Vec(0.7, 0.6, 0.5), 0));
            }else{
                std::cout << material << " is not supported as a material." << std::endl;
            }
        }
    } catch(std::exception&) {
        std::cout << "No cubes found" << std::endl;
    }
    return true;
}

hitable_list *SceneReader::getScene(){
    material *pink = new lambertian(new constant_texture(Vec(0.75, 0.25, 0.25)));
    material *white = new lambertian(new constant_texture(Vec(0.73, 0.73, 0.73)));
    material *blue = new lambertian(new constant_texture(Vec(0.25, 0.25, 0.75)));
    material *light = new diffuse_light(new constant_texture(Vec(7, 7, 7)));

    // ceiling
    list[pointer++] = new xz_plane(113, 443, 127, 432, 554, light);
    list[pointer++] = new flip_normals(new xz_plane(0, 555, 0, 555, 555, white));
    
    // left wall
    list[pointer++] = new flip_normals(new yz_plane(0, 555, 0, 555, 555, pink));

    // right wall
    list[pointer++] = new yz_plane(0, 555, 0, 555, 0, blue);
    // list[pointer++] = new yz_plane(100, 455, 100, 455, 0, light);

    // floor
    list[pointer++] = new xz_plane(0, 555, 0, 555, 0, white);

    // back wall
    list[pointer++] = new flip_normals(new xy_plane(0, 555, 0, 555, 555, white));

    return new hitable_list(list,pointer);
}

#endif