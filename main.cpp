#include "scene.h"
#include "renderer.cpp"

int main() {
    int width = 500; // The width in pixels
    int height = 500; // The height in pixels
    int sampelsPerPixel = 100; // The number of samples per pixel
    std::string filePath = "image.ppm"; // The file where the image will be saved
    std::string scenePath = "cornel_box.json"; // The file where the image will be saved

    // Retrieve the scene from the scene reader object
    SceneReader r(width, height, scenePath);
    Scene* scene = r.getScene();

    // render the scene
    Renderer render(width, height, sampelsPerPixel, filePath);
    render.renderScene(scene); // Start rendering
    std::cout << std::endl << "Rendering done!" << std::endl; 
}
