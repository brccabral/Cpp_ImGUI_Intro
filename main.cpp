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

void create_triangle ( unsigned int &vbo, unsigned int &vao, unsigned int &ebo )
{

    // create the triangle
    float triangle_vertices[] =
    {
        0.0f, 0.25f, 0.0f,	// position vertex 1
        1.0f, 0.0f, 0.0f,	 // color vertex 1
        0.25f, -0.25f, 0.0f,  // position vertex 1
        0.0f, 1.0f, 0.0f,	 // color vertex 1
        -0.25f, -0.25f, 0.0f, // position vertex 1
        0.0f, 0.0f, 1.0f,	 // color vertex 1
    };
    unsigned int triangle_indices[] =
    {
        0, 1, 2
    };
    glGenVertexArrays ( 1, &vao );
    glGenBuffers ( 1, &vbo );
    glGenBuffers ( 1, &ebo );
    glBindVertexArray ( vao );
    glBindBuffer ( GL_ARRAY_BUFFER, vbo );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( triangle_vertices ), triangle_vertices, GL_STATIC_DRAW );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof ( triangle_indices ), triangle_indices, GL_STATIC_DRAW );
    glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof ( float ), ( void * ) 0 );
    glEnableVertexAttribArray ( 0 );
    glVertexAttribPointer ( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof ( float ), ( void * ) ( 3 * sizeof ( float ) ) );
    glEnableVertexAttribArray ( 1 );
    glBindBuffer ( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray ( 0 );
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

    // create our geometries
    unsigned int vbo, vao, ebo;
    create_triangle ( vbo, vao, ebo );

    // init shader
    Shader triangle_shader;
    triangle_shader.init ( FileManager::read ( "assets/simple-shader.vs" ), FileManager::read ( "assets/simple-shader.fs" ) );

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

        // rendering our geometries
        triangle_shader.use();
        glBindVertexArray ( vao );
        glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );
        glBindVertexArray ( 0 );

        // render your GUI
        ImGui::Begin ( "Triangle Position/Color" );

        // * rotation control
        static float rotation = 0.0; // * initial value
        ImGui::SliderFloat ( "rotation", &rotation, 0, 2 * PI ); // * min, max

        // * translation control
        static float translation[] = {0.0, 0.0};
        ImGui::SliderFloat2 ( "position", translation, -1.0, 1.0 );

        // * color control
        static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
        ImGui::ColorEdit3 ( "color", color );

        ImGui::End();

        triangle_shader.setUniform ( "color", color[0], color[1], color[2] );
        triangle_shader.setUniform ( "rotation", rotation );
        triangle_shader.setUniform ( "translation", translation[0], translation[1] );

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
