# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
project( glad )
include_directories(include)
add_library(glad STATIC src/glad.c)

