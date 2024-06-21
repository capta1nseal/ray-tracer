# ray tracer

I (capta1nseal) watched Sebastian Lague's video on optimising a ray traced renderer using BVH traversal, and thought it would be a good time to make my own raytracer.
A certain scene with a cube-shaped room with perfect mirror walls got me thinking about how cool it would be to implement (visual) portals with a ray-traced renderer.
It then follows that the priorities of this project are:
- Implement a ray-traced renderer
- Optimise the renderer with BVH traversal
- Portals!

## project state

Currently, the project is a fully-implemented raytracer, fully inside the terminal.
By default, a basic scene is rendered and displayed to the terminal.
Each character is treated as 1 pixel, and 3x8-bit colour is used and assumed to be supported.
There is basic compensation for the difference between character width and height.

### technical details

This project relies only upon the c++20 standard, and the build-essential package, using make and g++.
(You could of course use almost any compiler).
There will be more requirements once a graphics pipeline is introduced.
Notable implemented features:
- An expansive 3D vector library, templated to different floating point precision levels.
- Basic 3D geometric primitives.
    - Their ray intersection algorithms.
    - Templates for higher floating point precision.
    - Some tools to store and access arbitrary primitives in one std::vector.
- Some classes encapsulating those types that then store and render the scene.
- Shading model and demo rendering is now in the application wrapper, and will later be encapsulated into computation and graphics interface classes.

#### geometry

For now, the following definitions are used as geometric ground truth:
- An orientation of 0,0,0 (roll,pitch,yaw) is towards positive x, with positive y to the left, and positive z up.
- roll is anticlockwise facing positive x, pitch is anticlockwise facing positive y, yaw is anticlockwise facing positive z.
- yaw is applied first, then pitch, then roll.
- azimuth is a synonym for yaw, altitude is a synonym for pitch.
