# ray tracer

I (capta1nseal) watched Sebastian Lague's video on optimising a ray traced renderer using BVH traversal, and thought it would be a good time to make my own raytracer.
A certain scene with a cube-shaped room with perfect mirror walls got me thinking about how cool it would be to implement (visual) portals with a ray-traced renderer.
It then follows that the priorities of this project are:
- Implement a ray-traced renderer
- Optimise the renderer with BVH traversal
- Portals!

## project state

The backbone of a ray tracer has been built, and can project the geometry of parallelograms and spheres.
By default, a basic scene with a sphere above 4 parallelograms is outputted to the terminal.
It is minimally shaded based on the x and y components of the normal at the intersection point.

### technical details

This project relies only upon the c++20 standard, and the build-essential package.
(you could of course use almost any compiler)
There will be more requirements once a graphics pipeline is introduced.
Notable implemented features:
- An expansive 3D vector library
- Basic 3D geometric primitives
    - Their ray intersection algorithms
    - Some tools to store and access arbitrary primitives in the same std::vector
- Some classes encapsulating those types to create behaviour

#### geometry

For now, the following definitions are used as geometric ground truth:
- An orientation of 0,0,0 (roll,pitch,yaw) is towards positive x, with positive y to the right, and positive z up
- Roll does nothing for now, to be changed soon. yaw is applied first, then pitch
- In 3D directions, azimuth is a synonym for yaw, altitude is a synonym for pitch
