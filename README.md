Ray-Tracing Project

This project is a basic implementation of a ray tracing engine designed to simulate light interactions with 3D objects and render realistic images. It demonstrates concepts such as reflection, refraction, shadows, and texture mapping.
Features

    Ray Tracing Engine: Simulates light behavior to render realistic scenes.
    Bitmap Rendering: Outputs the rendered scene as a .bmp image.
    Texture Mapping: Supports textures for enhanced visual realism using .bmp files.
    Scene Customization: Define objects, light sources, and camera parameters via input files.

File Overview

    main.cpp: Core implementation of the ray tracing algorithm.
    bitmap_image.hpp: Utility for handling bitmap images.
    input.txt: Configuration file to define the scene's objects, materials, and light sources.
    texture_b.bmp and texture_w.bmp: Sample texture files used for rendering.
    out.bmp: Generated output image of the rendered scene.
    description.txt: Additional notes or documentation about the project.
    .vscode/settings.json: Configuration file for Visual Studio Code to streamline debugging and development.

Getting Started
Prerequisites

    A C++ compiler such as GCC or Clang.
    An image viewer capable of opening .bmp files.

Setup and Execution

    Clone the repository and navigate to the project directory.
    Compile the code using:

g++ -o raytracer main.cpp

Prepare the scene by editing input.txt with desired objects, materials, and lights.
Run the program:

    ./raytracer

    View the output in out.bmp using any compatible image viewer.

Inputs and Outputs

    Input: Define scene objects, materials, light sources, and camera settings in input.txt.
    Output: A .bmp image (out.bmp) showing the rendered scene.

Sample Usage

    Modify input.txt to create a custom scene with different objects and lights.
    Replace or add textures in .bmp format to experiment with surface appearances.
    Compile and execute the program to see how changes affect the rendered image.

Future Improvements

    Add support for complex geometries (e.g., spheres, cones, and bezier surfaces).
    Enhance the shading model to include advanced techniques like Phong shading.
    Optimize rendering for larger, more detailed scenes.
    Add anti-aliasing for smoother edges in the rendered image.

License

This project is for educational purposes and demonstrates the fundamental principles of ray tracing.
