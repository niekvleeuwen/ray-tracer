#include <iostream>
#include <fstream>
#include "scene.h"
#include "random.h"
#include "scene_reader.h"

int main() {
    int width = 500; // in pixels
    int height = 500; // in pixels
    int sampelsPerPixel = 10; // number of samples per pixel
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
            Vec color(0, 0, 0);
            // for a given pixel take several samples with the random function within that pixel and send rays through each of the samples
            for (int s = 0; s < sampelsPerPixel; s++) {
                double u = double(j + random_double()) / double(width);
                double v = double(i + random_double()) / double(height);
                color = color + world->getColor(u,v);
            }
            // average the colors
            color = color / double(sampelsPerPixel);
            // raising the color to the power of 1/gamma,
            color = Vec(sqrt(color.getX()), sqrt(color.getY()), sqrt(color.getZ()));
            // write the colors to the file
            img << int(255.99*color.getX()) << " " << int(255.99*color.getY()) << " " << int(255.99*color.getZ()) << "\n";
        }
    }
}
