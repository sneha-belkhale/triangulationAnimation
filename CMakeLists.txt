project(Triangulation)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

find_package(OpenCV REQUIRED)
add_library(Triangle Triangle.hpp Triangle.cpp)
add_library(TriSubdiv TriSubdiv.hpp TriSubdiv.cpp)
# Project Executable
add_executable (triangulation triangulation.cpp)
target_link_libraries(triangulation TriSubdiv)
target_link_libraries(triangulation Triangle)
target_link_libraries(triangulation ${OpenCV_LIBS})