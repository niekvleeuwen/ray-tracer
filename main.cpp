#include <iostream>
#include <fstream>
#include "sphere.h"
#include "camera.cpp"
#include "scene.h"
#include "material.h"
#include "random.h"
#include "cube.cpp"
#include "scene_reader.h"

int main() {
    int width = 500; // in pixels
    int height = 500; // in pixels
    int sampelsPerPixel = 100; // number of samples per pixel
    std::string filePath = "image.ppm"; // the file where the image will be saved

    SceneReader *r = new SceneReader(width, height);

    // retrieve the scene from the scene reader object
    Scene *world = r->getScene();

    // open the image
    std::ofstream img;
    img.open(filePath);

    // P3 means this is a RGB color image in ASCII
    // 255 is the maximum value for each color
    img << "P3\n" << width << " " << height << "\n255\n";

    // loop trough every pixel
    for (int i = height; i >= 0; i--) {
        fprintf(stderr,"\rRendering (%d rows left)", i); 
        for (int j = 0; j < width; j++) {
            Vec col(0, 0, 0);
            // for a given pixel take several samples with the random function within that pixel and send rays through each of the samples
            for (int s = 0; s < sampelsPerPixel; s++) {
                double u = double(j + random_double()) / double(width);
                double v = double(i + random_double()) / double(height);
                col = col + world->trace(u,v);
            }
            // average the colors
            col = col / double(sampelsPerPixel);
            // raising the color to the power 1/gamma,
            col = Vec(sqrt(col.getX()), sqrt(col.getY()), sqrt(col.getZ()));
            // write the colors to the file
            img << int(255.99*col.getX()) << " " << int(255.99*col.getY()) << " " << int(255.99*col.getZ()) << "\n";
        }
    }
}
