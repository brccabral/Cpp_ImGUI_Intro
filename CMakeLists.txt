cmake_minimum_required(VERSION 3.21)
project(ImGUI_Intro)

include(GNUInstallDirs)

if ("${IMGUI_DIR}" STREQUAL "")
message(SEND_ERROR "define IMGUI_DIR")
return()
endif()

message("IMGUI_DIR ${IMGUI_DIR}")

set(SOURCES "${IMGUI_DIR}/imgui.cpp;${IMGUI_DIR}/imgui_demo.cpp;${IMGUI_DIR}/imgui_draw.cpp;${IMGUI_DIR}/imgui_tables.cpp;${IMGUI_DIR}/imgui_widgets.cpp;${IMGUI_DIR}/backends/imgui_impl_glfw.cpp;${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp")

add_executable(${PROJECT_NAME} main.cpp file_manager.cpp opengl_shader.cpp ${SOURCES})

if(WIN32)
if ("${GLFW_DIR}" STREQUAL "")
message(SEND_ERROR "define GLFW_DIR")
return()
endif()
message("GLFW_DIR ${GLFW_DIR}")

if ("${GLEW_DIR}" STREQUAL "")
message(SEND_ERROR "define GLEW_DIR")
return()
endif()
message("GLEW_DIR ${GLEW_DIR}")

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_DIR}/include ${GLEW_DIR}/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${GLFW_DIR}/lib-vc2022 ${GLEW_DIR}/lib/Release/x64)
target_link_libraries(${PROJECT_NAME} glfw3 opengl32 glew32)
target_link_options(${PROJECT_NAME} PUBLIC /NODEFAULTLIB:msvcrt)

else()

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw GLEW GL X11 GLU OpenGL)

endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${IMGUI_DIR};${IMGUI_DIR}/backends")
install(TARGETS ${PROJECT_NAME})

install(DIRECTORY
    ${PROJECT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

configure_file("${GLEW_DIR}/bin/Release/x64/glew32.dll" "${CMAKE_CURRENT_BINARY_DIR}/glew32.dll" COPYONLY)
install(FILES ${GLEW_DIR}/bin/Release/x64/glew32.dll
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR})