#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "opengl_shader.h"
#include "file_manager.h"
#include <stdio.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define PI 3.14159265358979323846

static void glfw_error_callback ( int error, const char *description )
{
    fprintf ( stderr, "Glfw Error %d: %s\n", error, description );
}

int main ( int, char ** )
{
    // Setup window
    glfwSetErrorCallback ( glfw_error_callback );
    if ( !glfwInit() )
        return 1;

    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 0 );
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow ( 1280, 720, "Dear ImGui - Conan", NULL, NULL );
    if ( window == NULL )
        return 1;

    glfwMakeContextCurrent ( window );
    glfwSwapInterval ( 1 ); // Enable vsync

    bool err = glewInit() != GLEW_OK;

    if ( err )
    {
        fprintf ( stderr, "Failed to initialize OpenGL loader!\n" );
        return 1;
    }

    int screen_width, screen_height;
    glfwGetFramebufferSize ( window, &screen_width, &screen_height );
    glViewport ( 0, 0, screen_width, screen_height );

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL ( window, true );
    ImGui_ImplOpenGL3_Init ( glsl_version );
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    while ( !glfwWindowShouldClose ( window ) )
    {
        glfwPollEvents();
        glClearColor ( 0.45f, 0.55f, 0.60f, 1.00f );
        glClear ( GL_COLOR_BUFFER_BIT );

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );

        int display_w, display_h;
        glfwGetFramebufferSize ( window, &display_w, &display_h );
        glViewport ( 0, 0, display_w, display_h );
        glfwSwapBuffers ( window );
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow ( window );
    glfwTerminate();

    return 0;
}
