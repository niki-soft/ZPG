//
// Created by Jan Mikulenka on 27.11.2021.
//

#ifndef ZPG_GAME_TEXTUREDMODEL_H
#define ZPG_GAME_TEXTUREDMODEL_H

#include "Model.h"

#include <vector>
#include <algorithm>
#include <string>
#include </usr/local/Cellar/glew/2.2.0_1/include/GL/glew.h> // include GLEW and new version of GL on Windows
#include </usr/local/Cellar/glfw/3.3.4/include/GLFW/glfw3.h> //include GLFW

//Include OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

class TexturedModel : public Model {

public:
    TexturedModel(std::vector<float>);
    void initialize();

};
#endif //ZPG_GAME_TEXTUREDMODEL_H
