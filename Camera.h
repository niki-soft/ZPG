//
// Created by Jan Mikulenka on 30.10.2021.
//

#ifndef ZPG_GAME_CAMERA_H
#define ZPG_GAME_CAMERA_H

#include </usr/local/Cellar/glew/2.2.0_1/include/GL/glew.h> // include GLEW and new version of GL on Windows
#include </usr/local/Cellar/glfw/3.3.4/include/GLFW/glfw3.h> //include GLFW

//Include GLM
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/glm.hpp>
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/vec3.hpp> // glm::vec3
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/vec4.hpp> // glm::vec4
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/mat4x4.hpp> // glm::mat4
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>


class Shader;

struct keyPress{
    int key;
    int scancode;
    int action;
    int mods;
};


class Camera {

private:
    std::vector<Shader*> shaders;

public:
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    int width;
    int height;
    void addShader(Shader* shader);

    float speed = 0.1f;
    float sensitivity = 100.0f;

    void Matrix(float FOVdeg, float nearPlane, float farPlane);

    void Inputs(keyPress *keyScan);
    void cameraChanged();
    Camera(Shader *shader, int width, int height, glm::vec3 position );
};


#endif //ZPG_GAME_CAMERA_H
