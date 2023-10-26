# **De Orb Engine**
De Orb Game Engine.<br>
>***Note**: The is engine is in active development.*

***
## Getting Started
Visual Studio 2022 is recommended, De Orb Engine is untested on other development environments whilst I focus on a Windows build.

**1. <ins>Downloading the repository</ins>:**

Start by cloning the repository with `git clone --recursive https://github.com/SionGRG/OrbEngine`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

**2. <ins>Configuring the dependencies</ins>:**

1. Run the [Setup.bat](https://github.com/SionGRG/OrbEngine/blob/master/Scripts/Setup.bat) file found in the `Scripts` folder. This will download the required prerequisites for the project if they are not present yet.
2. One prerequisite is the Vulkan SDK. If it is not installed, the script will execute the `VulkanSDK.exe` file, and will prompt the user to install the SDK.
3. After installation, run the [Setup.bat](https://github.com/SionGRG/OrbEngine/blob/master/Scripts/Setup.bat) file again. If the Vulkan SDK is installed properly, it will then obtain the Vulkan SDK Debug libraries. (This may take a longer amount of time)
4. After downloading and unzipping the files, the [Win-GenProjects.bat](https://github.com/SionGRG/OrbEngine/blob/master/Scripts/Win-GenProjects.bat) script file will get executed automatically, which will then generate a Visual Studio solution file for user's usage.

If changes are made, or if you want to regenerate project files, rerun the [Win-GenProjects.bat](https://github.com/SionGRG/OrbEngine/blob/master/Scripts/Win-GenProjects.bat) script file found in the `Scripts` folder.

***
## **Credits**
### ***Special Thanks***
>Special thanks to **The Cherno** and his **[Game Engine Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)** on YouTube.
>* **[The Cherno YouTube](https://www.youtube.com/@TheCherno)**
>* The Cherno's **[Hazel](https://github.com/TheCherno/Hazel) Engine**
>***
### ***Libraries***
>* **[spdlog](https://github.com/gabime/spdlog)**: C++ Logging Library.
>* **[GLFW](https://github.com/glfw/GLFW)**: an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development.
>* **[Glad](https://glad.dav1d.de/)**: a multi-language Vulkan/GL/GLES/EGL/GLX/WGL loader-generator based on the official specifications.
>* **[Dear ImGui](https://github.com/ocornut/imgui)**: Graphical User interface for C++.
>* **[ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)**: Immediate mode 3D gizmo for scene editing and other controls based on Dear Imgui.
>* **[glm](https://github.com/g-truc/glm)**: Math library.
>* **[stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)** from **[stb](https://github.com/nothings/stb/tree/master)**: Image file loader.
>* **[EnTT](https://github.com/skypjack/entt)**: Entity Component System.
>* **[yaml-cpp](https://github.com/jbeder/yaml-cpp)**: A YAML parser and emitter in C++.
>* **[Box2D](https://box2d.org/documentation/)**: A 2D rigid body simulation library for games.
>* **[Vulkan](https://www.vulkan.org/)**: A next generation graphics and compute API that provides high-efficiency, cross-platform access to modern GPUs.y
>* **[SPIR-V](https://www.khronos.org/spir/)**: The Industry Open Standard Intermediate Language for Parallel Compute and Graphics. SPIR-V is catalyzing a revolution in the ecosystem for shader and kernel language compilers used for expressing parallel computation and GPU-based graphics.
>* **[Mono](https://www.mono-project.com/)**: An open source implementation of Microsoft's .NET Framework, originally designed to bring .NET languages (mostly C#) to platforms other than Windows. I referenced a very good [Mono documentation](http://nilssondev.com/mono-guide/book/) created by **[Perter Nilsson](http://nilssondev.com/)**.
>***
