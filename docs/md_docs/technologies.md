# Our Project Stack

## Programming Languages

Before kicking off the programming of our R-Type we had compare and choose a specific object-oriented language :

| Language          | Paradigms                   | Key Features                                   | Ease of Use       | Performance        | Use Cases                      |
|--------------------|-----------------------------|-----------------------------------------------|-------------------|--------------------|---------------------------------|
| **C++**           | Object-oriented, Procedural | High-performance, manual memory management, cross-platform support | Moderate          | High               | Game engines, system software, embedded systems |
| **Java**          | Object-oriented            | Platform-independent (JVM), rich standard library, strong typing | Easy              | Moderate           | Enterprise apps, Android development, web servers |
| **Python**        | Object-oriented, Multi-paradigm | Dynamic typing, extensive libraries, simple syntax | Very Easy         | Moderate           | Web apps, data science, automation, AI/ML       |
| **C#**            | Object-oriented, Multi-paradigm | Strong integration with .NET, automatic memory management (GC), LINQ | Easy              | Moderate to High   | Windows apps, game development (Unity), web apps |
| **Ruby**          | Object-oriented            | Dynamic typing, concise syntax | Easy              | Moderate           | Web development (Rails), prototyping             |

We ultimately chose C++ because of its high performance, wide array of very useful libraries and the one where we're the most experienced in.

<p align="center">
  <img src="docs/assets/cpp-logo.png" alt="R-Type" width="277" height="300">
</p>

------

## Graphical libraries

During our project we had to choose between several C++ graphical libs :

| Library           | Features                            | Platforms          | Ease of Use       | Documentation          | Use Cases                     |
|--------------------|-------------------------------------|--------------------|-------------------|-------------------------|--------------------------------|
| **SFML**          | 2D graphics, audio, input, and more| Windows, macOS, Linux | Easy              | Comprehensive tutorials | Game development, simple apps|
| **SDL**           | 2D rendering, input, audio, multi-window | Cross-platform    | Moderate          | Good examples, detailed | Games, multimedia applications|
| **OpenGL (via GLFW/GLEW)** | Low-level 2D/3D rendering APIs | Cross-platform    | Hard              | Detailed but technical  | 3D graphics, visualization    |
| **DirectX**       | Low-level 2D/3D rendering APIs     | Windows only       | Hard              | Extensive, Windows SDK  | Windows-specific 3D apps      |
| **Vulkan**        | High-performance, modern graphics  | Cross-platform    | Very Hard         | Detailed but complex    | Advanced 3D rendering, engines|
| **OGRE (Object-Oriented Graphics Rendering Engine)** | High-performance 3D graphics | Cross-platform | Moderate          | Detailed, developer-focused | 3D games, simulation         |

<p align="center">
  <img src="docs/assets/sfml-logo.png" alt="R-Type" width="600">
</p>

But in the end we chose SFML due to its ease of use, cross-platform compatibility and that it fit our use case the most as we needed to make a 2D game.