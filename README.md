# ray-tracer
Object-oriented ray tracer written in C++ 

![Cornell Box](https://raw.githubusercontent.com/niekvleeuwen/ray-tracer/blob/master/renders/cornel_box_5000ssp.png)

## Renders
Render time for the cornell box on a i5-8250u

| Resolution    | Sampels Per Pixel| Render time|
| ------------- |------------------| -----------|
| 500x500       | 10               | 9.38s      |
| 500x500       | 100              | 1m19s      |
| 500x500       | 1000             | 13m20s     |

## Features
* Support for Spheres, Cubes and Planes
* Diffuse and reflection
* Multiple lights
* Movable camera with a user controlled FOV and position
* Scene reader 

## Todo
* Add support for more shapes
* Multithreading
* Textures
