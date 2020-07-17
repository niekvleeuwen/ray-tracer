# ray-tracer
Object-oriented ray tracer written in C++ 

![Cornell Box](https://raw.githubusercontent.com/niekvleeuwen/ray-tracer/master/renders/cornel_box_5000ssp.png)

## Installation

The installation process is quite simple

> Clone this repository and execute the following command
```shell
$ make
```

## Renders
Render time for the cornell box on a i5-8250u

| Resolution    | Sampels Per Pixel| Render time|
| ------------- |------------------| -----------|
| 100x100       | 10               | 0.27s      |
| 100x100       | 100              | 2.32s      |
| 100x100       | 1000             | 23.93s     |
| 100x100       | 10000            | 4m34s      |
| 500x500       | 10               | 6.38s      |
| 500x500       | 100              | 1m7s       |
| 500x500       | 1000             | 11m27s     |
| 1000x1000     | 10               | 28.16s     |
| 1000x1000     | 100              | 4m41s      |
| 1000x1000     | 1000             | 45m58s     |

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
