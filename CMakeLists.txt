cmake_minimum_required(VERSION 3.21)
project(ImGUI_Intro)

include(GNUInstallDirs)

find_package(glfw3 REQUIRED)

if ("${IMGUI_DIR}" STREQUAL "")
    message(SEND_ERROR "define IMGUI_DIR")
    return()
endif()

message("IMGUI_DIR ${IMGUI_DIR}")

set(SOURCES "${IMGUI_DIR}/imgui.cpp;${IMGUI_DIR}/imgui_demo.cpp;${IMGUI_DIR}/imgui_draw.cpp;${IMGUI_DIR}/imgui_tables.cpp;${IMGUI_DIR}/imgui_widgets.cpp;${IMGUI_DIR}/backends/imgui_impl_glfw.cpp;${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp")

add_executable(${PROJECT_NAME} main.cpp file_manager.cpp opengl_shader.cpp ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${IMGUI_DIR};${IMGUI_DIR}/backends")
target_link_libraries(${PROJECT_NAME} glfw GLEW GL X11 GLU OpenGL)
install(TARGETS ${PROJECT_NAME})

install(DIRECTORY
    ${PROJECT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
