//
// Created by Jan Mikulenka on 25.10.2021.
//

#ifndef ZPG_GAME_MODEL_H
#define ZPG_GAME_MODEL_H

#include <vector>
#include <algorithm>
#include </usr/local/Cellar/glew/2.2.0_1/include/GL/glew.h> // include GLEW and new version of GL on Windows
#include </usr/local/Cellar/glfw/3.3.4/include/GLFW/glfw3.h> //include GLFW

class Model {
private:
    GLuint VAO;
    GLuint VBO;
    int triangle_count;
    float *points;

public:
    Model(std::vector<float> pnts);
    void setVAO();
    int numberOfTriangles();
};


#endif //ZPG_GAME_MODEL_H
