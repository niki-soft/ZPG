//
// Created by Jan Mikulenka on 25.10.2021.
//

#ifndef ZPG_TEST_TRANSFORM_H
#define ZPG_TEST_TRANSFORM_H

#include </usr/local/Cellar/glew/2.2.0_1/include/GL/glew.h> // include GLEW and new version of GL on Windows
#include </usr/local/Cellar/glfw/3.3.4/include/GLFW/glfw3.h>

//Include GLM
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/glm.hpp>
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/vec3.hpp> // glm::vec3
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/vec4.hpp> // glm::vec4
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/mat4x4.hpp> // glm::mat4
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>
#include <utility>
#include <string>

struct transStruct{
    std::string text;
    float number;
    glm::vec3 vct;
};

class Transform {

private:
    std::vector<transStruct> trans;

public:
    Transform();
    glm::mat4 M;
    void addTransform(transStruct t);
    void removeTransform(transStruct t);
    void calculateTransform();

#endif //ZPG_TEST_TRANSFORM_H
};