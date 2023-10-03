# ImGUI Intro

Tutorial "Introduction to the ImGui C++ Library with Conan"  
https://www.youtube.com/watch?v=O2E-W9P-jKc

- Clone the repo
    - `git clone https://github.com/ocornut/imgui`
- Install glfw3 and glew
    - `sudo apt install libglfw3-dev libglew-dev`
- Add to include path
    - `path/to/imgui`
    - `path/to/imgui/backends`
- Check glfw3 and glew flags
    - `pkg-config --static --libs glfw3`
    - `pkg-config --cflags glfw3`
    - `pkg-config --static --libs glew`
    - `pkg-config --cflags glew`
- Compile all these sources
    - main.cpp
    - file_manager.cpp
    - opengl_shader.cpp
    - $(IMGUI_DIR)/imgui.cpp
    - $(IMGUI_DIR)/imgui_demo.cpp
    - $(IMGUI_DIR)/imgui_draw.cpp
    - $(IMGUI_DIR)/imgui_tables.cpp
    - $(IMGUI_DIR)/imgui_widgets.cpp
    - $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp
    - $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
