#include "renderer.h"
#include "scene_reader.cpp"

Renderer::Renderer(int _width, int _height, int _sampelsPerPixel, std::string _filePath){
    width = _width;
    height = _height;
    sampelsPerPixel = _sampelsPerPixel;
    filePath = _filePath;
    initFile();
}

// This function renders retrieves a scene from the scene reader and renders the scene to an image
bool Renderer::renderScene(RayTracer *scene){
    std::cout << "Starting with the render..." << std::endl;
    // Loop trough every pixel
    for (int i = height; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            Vec color(0, 0, 0);
            // For a given pixel take several samples with the random function within that pixel and send rays through each of the samples
            for (int s = 0; s < sampelsPerPixel; s++) {
                double sampleX = double(j + rand() / (RAND_MAX + 1.0)) / double(width);
                double sampleY = double(i + rand() / (RAND_MAX + 1.0)) / double(height);
                color = color + scene->getColor(sampleX,sampleY);
            }
            // Average the colors
            color = color / double(sampelsPerPixel);
            // Raising the color to the power of 1/gamma,
            color = Vec(sqrt(color.getX()), sqrt(color.getY()), sqrt(color.getZ()));
            writeColorToFile(color);
        }
        // Display the current procentage
        updateProgressBar(i);
    }
    return true;
}

// This function initializes the file
void Renderer::initFile(){
    // Open the image
    img.open(filePath);

    // P3 means this is a RGB color image in ASCII
    // 255 is the maximum value for each color
    img << "P3\n" << width << " " << height << "\n255\n";

}

// This function writes the color to the specified file
void Renderer::writeColorToFile(Vec color){
    // Write the colors to the file
    img << int(255.99*color.getX()) << " " << int(255.99*color.getY()) << " " << int(255.99*color.getZ()) << "\n";  
}

// This function takes the rowsDone, calculates a percentages and displays it on the screen
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