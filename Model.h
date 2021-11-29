//
// Created by Jan Mikulenka on 25.10.2021.
//

#ifndef ZPG_GAME_MODEL_H
#define ZPG_GAME_MODEL_H

#include <vector>
#include "Shader.h"
#include <algorithm>
#include <string>
#include </usr/local/Cellar/glew/2.2.0_1/include/GL/glew.h> // include GLEW and new version of GL on Windows
#include </usr/local/Cellar/glfw/3.3.4/include/GLFW/glfw3.h> //include GLFW

// Include SOIL
//#include "/Users/jenda/Documents/GitHub/soil/libSOIL/SOIL.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include </Users/jenda/Documents/GitHub/stb/stb_image.h>
//#include "/Users/jenda/Documents/GitHub/stb/stb_image_write.h"

//Include OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


class Model {
protected:
    GLuint VAO;
    GLuint VBO;
    int triangle_count;
    float *points;
    int number;

public:
    Model(std::vector<float> pnts);
    void setVAO();
    int numberOfTriangles();
    void initialize();
};

#endif //ZPG_GAME_MODEL_H
