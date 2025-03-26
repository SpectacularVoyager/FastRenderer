cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build) 

project(project VERSION 1.0.0)

cmake_policy(SET CMP0072 NEW) #SET OPENGL TO CORE

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(project ${SOURCES})

add_subdirectory(include/imgui)
target_link_libraries(project imgui)

find_package(GLEW REQUIRED)
target_link_libraries(project GLEW::GLEW)
find_package(OpenGL REQUIRED)
target_link_libraries(project glfw OpenGL::GL)
find_package(glm REQUIRED)
target_link_libraries(project glm::glm)
find_package(assimp REQUIRED)
target_link_libraries(project assimp::assimp)

target_include_directories(project PRIVATE include)
target_include_directories(project PRIVATE src)
# FIND_PACKAGE( OpenCV REQUIRED )                              
# INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
# TARGET_LINK_LIBRARIES (project ${OpenCV_LIBS})         

### dependencies
#	sudo apt-get install libglfw3-dev
#	sudo apt-get install libglew-dev
#	sudo apt install libglm-dev
