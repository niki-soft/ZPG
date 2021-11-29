cmake_minimum_required(VERSION 3.20)
project(zpg-game)

set(CMAKE_CXX_STANDARD 14)

# Add header file
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
set(GLM_HPP /usr/local/Cellar/glm/0.9.9.8/include/glm/glm.hpp)
set(SOIL /Users/jenda/Documents/GitHub/soil/libSOIL/SOIL.h)
#set(STB "/Users/jenda/Documents/GitHub/stb/stb_image.h")
include_directories(${GLEW_H} ${GLFW_H} ${GLM_HPP} ${SOIL})

ADD_LIBRARY( SOIL_STATIC
        /Users/jenda/Documents/GitHub/soil/libSOIL/image_helper.c
        /Users/jenda/Documents/GitHub/soil/libSOIL/stb_image_aug.c
        /Users/jenda/Documents/GitHub/soil/libSOIL/image_DXT.c
        /Users/jenda/Documents/GitHub/soil/libSOIL//SOIL.c
        )

# Add target links
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.dylib)
set(SOIL_LINK /Users/jenda/Documents/GitHub/soil/libSOIL/libSOIL.dylib)
#add_library(STB_IMAGE /Users/jenda/Documents/GitHub/stb/stb_image.c)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${SOIL_STATIC} ${SOIL_LINK})

set(SOURCE_FILES main.cpp)
add_executable(zpg-game main.cpp Render.cpp Render.h Object.cpp Object.h Shader.cpp Shader.h Model.cpp Model.h Transform.cpp Transform.h Scene.cpp Scene.h Storage.cpp Storage.h ObjectFactory.cpp ObjectFactory.h Camera.cpp Camera.h TexturedModel.cpp TexturedModel.h ShaderLoader.cpp ShaderLoader.h)

find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${OpenCV_INCLUDE_DIR})

target_link_libraries(zpg-game ${OPENGL_LIBRARIES} ${OpenCV_LIBS})
