# ray tracer

I (capta1nseal) watched Sebastian Lague's video on optimising a ray traced renderer using BVH traversal, and thought it would be a good time to make my own raytracer.
A certain scene with a cube-shaped room with perfect mirror walls got me thinking about how cool it would be to implement (visual) portals with a ray-traced renderer.
It then follows that the priorities of this project are:
- implement a ray-traced renderer
- optimise the renderer with BVH traversal
- portals!

## project state

The backbone of a ray tracer has been built, and can project the geometry of any parallelogram, rectangle or square to the screen.

### geometry

For now, the following definitions are used as geometric ground truth:
- an orientation of 0,0,0 (roll,pitch,yaw) is towards positive x, with positive y to the right, and positive z up
- in 3D directions, azimuth is a synonym for yaw, altitude is a synonym for pitch
