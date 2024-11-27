cmake_minimum_required(VERSION 3.12)
project(FireSim)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required packages
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
    ${SDL2_INCLUDE_DIRS}
)

# Gather source files
file(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)

# ImGui source files
set(IMGUI_SRCS
    ${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_sdl2.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Create executable
add_executable(firesim 
    ${SRCS}
    ${IMGUI_SRCS}
)

# Link libraries
target_link_libraries(firesim
    ${SDL2_LIBRARIES}
    OpenGL::GL
    GLEW::GLEW
)

# Compiler warnings
if(MSVC)
    target_compile_options(firesim PRIVATE /W4)
else()
    target_compile_options(firesim PRIVATE -Wall -Wextra -Wswitch-enum)
endif()

