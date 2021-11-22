cmake_minimum_required(VERSION 3.20)
project(zpg-game)

set(CMAKE_CXX_STANDARD 14)

# Add header file
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
set(GLM_HPP /usr/local/Cellar/glm/0.9.9.8/include/glm/glm.hpp)
include_directories(${GLEW_H} ${GLFW_H} ${GLM_HPP})

# Add target link
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.dylib)
set(SOIL_LIBRARY /opt/local/lib/libSOIL.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${SOIL_LIBRARY})

set(SOURCE_FILES main.cpp)
add_executable(zpg-game main.cpp Render.cpp Render.h Object.cpp Object.h Shader.cpp Shader.h Model.cpp Model.h Transform.cpp Transform.h Scene.cpp Scene.h Storage.cpp Storage.h ObjectFactory.cpp ObjectFactory.h Camera.cpp Camera.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(zpg-game ${OPENGL_LIBRARIES} /opt/local/lib/libSOIL.a)
