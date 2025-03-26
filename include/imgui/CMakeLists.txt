cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build) 

project(project VERSION 1.0.0)

cmake_policy(SET CMP0072 NEW) #SET OPENGL TO CORE

set(CMAKE_CXX_STANDARD 17)


file(GLOB_RECURSE IMGUI_SOURCES "*.cpp")

add_library(imgui STATIC ${IMGUI_SOURCES})
