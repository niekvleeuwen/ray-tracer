#include "renderer.h"
#include "scene.h"
#include "scene_reader.h"
#include <unistd.h>

Renderer::Renderer(int _width, int _height, int _sampelsPerPixel, std::string _filePath){
    width = _width;
    height = _height;
    sampelsPerPixel = _sampelsPerPixel;
    filePath = _filePath;
}

// this function 
bool Renderer::render(){
     SceneReader *r = new SceneReader(width, height);

    // retrieve the scene from the scene reader object
    Scene *world = r->getScene();

    // open the image
    std::ofstream img;
    img.open(filePath);

    // P3 means this is a RGB color image in ASCII
    // 255 is the maximum value for each color
    img << "P3\n" << width << " " << height << "\n255\n";

    std::cout << "Starting with the render..." << std::endl;
    // loop trough every pixel
    for (int i = height; i >= 0; i--) {
        // fprintf(stderr,"\rRendering (%d rows left)", i); 
        for (int j = 0; j < width; j++) {
            Vec color(0, 0, 0);
            // for a given pixel take several samples with the random function within that pixel and send rays through each of the samples
            for (int s = 0; s < sampelsPerPixel; s++) {
                double u = double(j + rand() / (RAND_MAX + 1.0)) / double(width);
                double v = double(i + rand() / (RAND_MAX + 1.0)) / double(height);
                color = color + world->getColor(u,v);
            }
            // average the colors
            color = color / double(sampelsPerPixel);
            // raising the color to the power of 1/gamma,
            color = Vec(sqrt(color.getX()), sqrt(color.getY()), sqrt(color.getZ()));
            // write the colors to the file
            img << int(255.99*color.getX()) << " " << int(255.99*color.getY()) << " " << int(255.99*color.getZ()) << "\n";
        }
        updateProgressBar(i);
    }
    return true;
}

//this function takes the rowsDone, calculates a percentages and displays it on the screen
void Renderer::updateProgressBar(int rowsDone){
    // To get to a percentage first subtract rowsDone from the height, because rowsDone is descending, 
    float percentage = ((float)(height - rowsDone) / height) * 100;
    std::cout << "[";
    for(int i = 0; i < 50; i++){
        if(i < (percentage / 2)){ // percentage needs to be divided by 2 because the percentage bar is 50 width
            std::cout << "#";
        }else{
            std::cout << " ";
        }
    }
    std::cout << "] " << percentage << "% \r" << std::flush;
}