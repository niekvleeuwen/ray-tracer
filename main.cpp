#include "renderer.cpp"

int main() {
    int width = 500; // in pixels
    int height = 500; // in pixels
    int sampelsPerPixel = 10; // number of samples per pixel
    std::string filePath = "image.ppm"; // the file where the image will be saved

    Renderer render(width, height, sampelsPerPixel, filePath);
    render.render();
    std::cout << std::endl << "Rendering done!" << std::endl; 
}
