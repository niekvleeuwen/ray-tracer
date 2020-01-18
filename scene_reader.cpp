#include "scene_reader.h"
#include "scene.h"

SceneReader::SceneReader(int _widht, int _height, std::string _scenePath){
    width = _widht;
    height = _height;
    scenePath = _scenePath;
}

// This function parses the in the constructor given JSON file
int SceneReader::parseJson(){
    // read a file and parse to JSON
    std::cout << "Reading file..." <<std::endl;
    std::ifstream ifs(scenePath);
    try{
        scene = json::parse(ifs);
    }catch(std::exception&) {
        std::cout << "No file found or the file is not JSON formatted" << std::endl;
        exit(0);
    }
    return scene.size();
}

// This function converts the JSON object in a scene and returns it;
RayTracer *SceneReader::getScene(){
    this->parseJson();
    // give the array a size based on the number of objects in the scene
    list = new BasicObject*[scene.size() + 7];

    // init the camera object from the JSON object 
    Camera *cam;
    try{
        auto& array = scene.at("camera");
        int fieldOfView = array.at("fov");
        auto&& lookFromPoint = array.at("lookFromPoint");
        auto&& lookToPoint = array.at("lookToPoint");
        Vec cameraPosition(lookFromPoint.at("x"), lookFromPoint.at("y"), lookFromPoint.at("z"));
        Vec cameraLookTo(lookToPoint.at("x"), lookToPoint.at("y"), lookToPoint.at("z"));
        cam = new Camera(cameraPosition, cameraLookTo, fieldOfView, double(width)/double(height));
    } catch(std::exception&) {
        std::cout << "No camera found, add a camera to the Scene" << std::endl;
        exit(1);
    }

    // search for sphere key in the JSON
    try {
        auto& array = scene.at("sphere");
        //use a for loop for every sphere
        for (auto&& val: array) {
            std::string material = val.at("material");
            if(material == "diffuse"){
                auto&& color = val.at("color");
                list[pointer++] = new Sphere(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("radius"), new Diffuse(Vec(color.at("r"), color.at("g"), color.at("b"))));
            }else if(material == "reflective"){
                list[pointer++] = new Sphere(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("radius"), new Reflective(Vec(0.7, 0.6, 0.5)));
            }else{
                std::cout << material << " is not supported as a material." << std::endl;
            }
        }
    } catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // search for cube key in the JSON
    try {
        auto& array = scene.at("cube");
        for (auto&& val: array) {
            auto&& color = val.at("color");
            list[pointer++] = new Cube(Vec(val.at("x"), val.at("y"), val.at("z")), val.at("size"), new Diffuse(Vec(color.at("r"), color.at("g"), color.at("b"))));
        }
    } catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // search for plane key in the JSON
    try {
        auto& array = scene.at("plane");
        for (auto&& val: array) {
            std::string materialType = val.at("material");
            auto&& color = val.at("color");
            Material *material;
            std::string type = val.at("type");
            bool flipped = val.at("flipped");

            // First define the material
            if(materialType == "diffuse"){
                material = new Diffuse(Vec(color.at("r"), color.at("g"), color.at("b")));
            }else if(materialType == "light"){
                material = new Light(Vec(color.at("r"), color.at("g"), color.at("b")));
            }
            
            // Check which axis the plane has to be
            BasicObject *plane;
            if(type == "xy"){
                plane = new PlaneXY(val.at("a"), val.at("b"), val.at("c"), val.at("d"), val.at("z"), material);
            }else if(type == "xz"){
                plane = new PlaneXZ(val.at("a"), val.at("b"), val.at("c"), val.at("d"), val.at("z"), material);
            }else if(type == "yz"){
                plane = new PlaneYZ(val.at("a"), val.at("b"), val.at("c"), val.at("d"), val.at("z"), material);
            }

            // check if the plane is intended to be flipped
            if(flipped){
                list[pointer++] = new FlippedBasicObject(plane);
            }else{
                list[pointer++] = plane;
            }
        }
    } catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Build the new scene
    RayTracer *scene = new RayTracer(list, pointer);
    scene->setCamera(cam);
    return scene;
}
