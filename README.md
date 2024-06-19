# ray tracer

I (capta1nseal) watched Sebastian Lague's video on optimising a ray traced renderer using BVH traversal, and thought it would be a good time to make my own raytracer.
A certain scene with a cube-shaped room with perfect mirror walls got me thinking about how cool it would be to implement (visual) portals with a ray-traced renderer.
It then follows that the priorities of this project are:
- Implement a ray-traced renderer
- Optimise the renderer with BVH traversal
- Portals!

## project state

The backbone of a ray tracer has been built and is ready for proper bounce lighting.
By default, a basic scene with a sphere above some planar shapes is drawn with phong shading and path-traced shadows.
The output is currently outputted to the terminal as ASCII, with compensation for the difference between character width and height.
Even in the terminal, it has some decent dynamic range through a float-ASCII brightness lookup.

### technical details

This project relies only upon the c++20 standard, and the build-essential package, using make and g++.
(You could of course use almost any compiler).
There will be more requirements once a graphics pipeline is introduced.
Notable implemented features:
- An expansive 3D vector library, templated to different floating point precision levels.
- Basic 3D geometric primitives.
    - Their ray intersection algorithms.
    - Templates for higher floating point precision.
    - Some tools to store and access arbitrary primitives in the same std::vector.
- Some classes encapsulating those types to create behaviour.
    - Templated where it makes sense.
- Shading model and demo rendering is now in the application wrapper, and will later be encapsulated into computation and graphics interface classes.

#### geometry

For now, the following definitions are used as geometric ground truth:
- An orientation of 0,0,0 (roll,pitch,yaw) is towards positive x, with positive y to the left, and positive z up.
- roll is anticlockwise facing positive x, pitch is anticlockwise facing positive y, yaw is anticlockwise facing positive z.
- yaw is applied first, then pitch, then roll.
- azimuth is a synonym for yaw, altitude is a synonym for pitch.
