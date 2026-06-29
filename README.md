# GeneralCompute

An optimized, modern C++ rendering framework providing the foundational core graphics pipeline for a Hardware-in-the-Loop (HIL) simulation engine. Built on top of OpenGL 3.3 Core Profile, GLFW3, and GLAD.

## Features

- **Automated Shader Pipeline:** Encapsulated `Shader` class handles raw string loading, automated multi-stage compilation (`GL_COMPILE_STATUS`), and pipeline linking verification (`GL_LINK_STATUS`) behind the scenes.
- **VRAM Hygiene Management:** Fully RAII-compliant abstraction via custom C++ object lifecycles; class destructors seamlessly clear allocated hardware programs from GPU hardware resources (`glDeleteProgram`).
- **Clean Vertex Blueprints:** Structured coordinate matrices drafting seamless triangle layouts to connect multi-vertex quads without memory skewing.


## Project Structure

```text
GeneralCompute/
├── GeneralCompute.sln          # Visual Studio Solution Manifest
├── GeneralCompute/
│   ├── GeneralCompute.cpp      # Main application state logic and application render loop
│   ├── Shader.h                # Custom Shader abstraction blueprint declaration
│   ├── Shader.cpp              # Shader file reader, GLSL compilation, and lifecycle handler
│   ├── gl.c                    # GLAD multi-driver runtime loading source code
│   ├── .gitignore              # Repository tracking filtration asset
│   ├── Shaders/
│   │   ├── vertex.vert         # Core Vertex layout shader configuration
│   │   └── FragmentShader.frag # Pixel/Fragment coloring configuration (Orange Solid)
│   └── libraries/              # Project dependencies (GLFW3 static binaries & headers)
