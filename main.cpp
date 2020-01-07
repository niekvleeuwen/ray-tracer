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
    int width = 500; //in pixels
    int height = 500; //in pixels
    int sampelsPerPixel = 10; //number of samples per pixel

    SceneReader *r = new SceneReader();

    Scene *world = r->getScene();

    std::ofstream img;
    img.open("image.ppm");
    img << "P3\n" << width << " " << height << "\n255\n";
    // P3 means this is a RGB color image in ASCII
    // 255 is the maximum value for each color

    Vec cameraPostion(278, 278, -800);
    Vec cameraLookTo(278,278,0);

    Camera cam(cameraPostion, cameraLookTo, Vec(0,1,0), 37, float(width)/float(height));

    for (int i = height; i >= 0; i--) {
        fprintf(stderr,"\rRendering (%d rows left)", i); 
        for (int j = 0; j < width; j++) {
            Vec col(0, 0, 0);
            // For a given pixel i take several samples with the random function within that pixel and send rays through each of the samples
            for (int s = 0; s < sampelsPerPixel; s++) {
                double u = double(j + random_double()) / double(width);
                double v = double(i + random_double()) / double(height);
                Ray r = cam.get_ray(u, v);
                col = col + world->color(r, 0);
            }
            // Average the colors of the Rays
            col = col / double(sampelsPerPixel);
            col = Vec( sqrt(col.getX()), sqrt(col.getY()), sqrt(col.getZ()) );

            int ir = int(255.99*col.getX());
            int ig = int(255.99*col.getY());
            int ib = int(255.99*col.getZ());

            img << ir << " " << ig << " " << ib << "\n";
        }
    }
}
