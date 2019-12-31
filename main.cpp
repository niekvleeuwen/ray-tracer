#include <iostream>
#include <fstream>
#include "sphere.h"
#include "camera.cpp"
#include "hitable_list.h"
#include "material.h"
#include "random.h"
#include "rect.h"

Vec color(const Ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        Ray scattered;
        Vec attenuation;
        Vec emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
             return emitted + attenuation*color(scattered, world, depth+1);
        else
            return emitted;
    }
    else
        return Vec(0,0,0);
}

hitable *box() {
    hitable **list = new hitable*[11];
    int i = 0;
    material *pink = new lambertian(new constant_texture(Vec(0.75, 0.25, 0.25)));
    material *white = new lambertian(new constant_texture(Vec(0.73, 0.73, 0.73)));
    material *blue = new lambertian(new constant_texture(Vec(0.25, 0.25, 0.75)));
    material *light = new diffuse_light(new constant_texture(Vec(7, 7, 7)));

    // ceiling
    list[i++] = new xz_rect(113, 443, 127, 432, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    
    // left wall
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, pink));
    
    // right wall
    list[i++] = new yz_rect(0, 555, 0, 555, 0, blue);

    // floor
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);

    // back wall
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

    // spheres
    list[i++] = new sphere(Vec(160, 50, 145), 50, new diffuse(Vec(0.75,0.25,0.25)));
    list[i++] = new sphere(Vec(400, 100, 300), 100, new metal(Vec(0.7, 0.6, 0.5), 0));

    return new hitable_list(list,i);
}

int main() {
    int nx = 500; //width
    int ny = 500; //height
    int ns = 10; //number of samples per pixel

    hitable *world = box();

    std::ofstream img;
    img.open("image.ppm");
    img << "P3\n" << nx << " " << ny << "\n255\n";
    // P3 means this is a RGB color image in ASCII
    // 255 is the maximum value for each color

    Vec cameraPostion(278, 278, -800);
    Vec cameraLookTo(278,278,0);

    Camera cam(cameraPostion, cameraLookTo, Vec(0,1,0), 40, float(nx)/float(ny));

    for (int j = ny-1; j >= 0; j--) {
        fprintf(stderr,"\rRendering (%d rows left)", j); 
        for (int i = 0; i < nx; i++) {
            Vec col(0, 0, 0);
            // For a given pixel i take several samples with the random function within that pixel and send Rays through each of the samples
            for (int s = 0; s < ns; s++) {
                double u = double(i + random_double()) / double(nx);
                double v = double(j + random_double()) / double(ny);
                Ray r = cam.get_ray(u, v);
                col = col + color(r, world, 0);
            }
            // Average the colors of the Rays
            col = col / double(ns);
            col = Vec( sqrt(col.getX()), sqrt(col.getY()), sqrt(col.getZ()) );

            int ir = int(255.99*col.getX());
            int ig = int(255.99*col.getY());
            int ib = int(255.99*col.getZ());

            img << ir << " " << ig << " " << ib << "\n";
        }
    }
}
