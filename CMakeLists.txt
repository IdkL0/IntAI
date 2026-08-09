cmake_minimum_required(VERSION 3.10)
project(IntAI VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(GLFW_PLATFORM "all" CACHE STRING "szlp;k;fjsdklfsheiuo" FORCE)

set(GLFW_BUILD_WAYLAND ON CACHE BOOL "BUILD WITH WAYLAND SUPPORT" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "BUILD WITH X11 SUPPORT" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

add_subdirectory(src)