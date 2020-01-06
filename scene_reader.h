#ifndef SCENEREADERH
#define SCENEREADERH

#include <lib/json.hpp>
#include <vector>
#include <fstream>
#include <iostream>
using json = nlohmann::json;

class SceneReader{
    public:
        json scene;
        BasicObject **list;
        SceneReader(){
            list = new BasicObject*[10];
        }
        int pointer = 0;
        bool parseJson();
        hitable_list *getScene();
};

bool SceneReader::parseJson(){
    // read a file and parse to JSON
    std::ifstream ifs("scene.json");
    scene = json::parse(ifs);

    // spheres
    try {
        auto& array = scene.at("sphere");
        for (auto&& val: array) {
            list[pointer++] = new sphere(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("radius"), new metal(Vec(0.7, 0.6, 0.5), 0));
        }
    } catch(std::exception&) {
        std::cout << "No spheres" << std::endl;
    }

    return true;
}

hitable_list *SceneReader::getScene(){
    material *pink = new lambertian(new constant_texture(Vec(0.75, 0.25, 0.25)));
    material *white = new lambertian(new constant_texture(Vec(0.73, 0.73, 0.73)));
    material *blue = new lambertian(new constant_texture(Vec(0.25, 0.25, 0.75)));
    material *light = new diffuse_light(new constant_texture(Vec(7, 7, 7)));

    // ceiling
    list[pointer++] = new xz_rect(113, 443, 127, 432, 554, light);
    list[pointer++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    
    // left wall
    list[pointer++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, pink));

    // right wall
    list[pointer++] = new yz_rect(0, 555, 0, 555, 0, blue);
    // list[pointer++] = new yz_rect(100, 455, 100, 455, 0, light);

    // floor
    list[pointer++] = new xz_rect(0, 555, 0, 555, 0, white);

    // back wall
    list[pointer++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

    // spheres
    //list[pointer++] = new sphere(Vec(160, 50, 145), 50, new diffuse(Vec(0.75,0.25,0.25)));
    //list[pointer++] = new sphere(Vec(400, 100, 300), 100, new metal(Vec(0.7, 0.6, 0.5), 0));
    //list[pointer++] = new Cube(Vec(100, 0, 65), Vec(200, 100, 230), pink);

    return new hitable_list(list,pointer);
}

#endif