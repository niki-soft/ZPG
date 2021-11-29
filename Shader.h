//
// Created by Jan Mikulenka on 25.10.2021.
//

#ifndef ZPG_TEST_SHADER_H
#define ZPG_TEST_SHADER_H

#include </usr/local/Cellar/glew/2.2.0_1/include/GL/glew.h> // include GLEW and new version of GL on Windows
#include </usr/local/Cellar/glfw/3.3.4/include/GLFW/glfw3.h> //include GLFW

//Include GLM
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/glm.hpp>
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/vec3.hpp> // glm::vec3
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/vec4.hpp> // glm::vec4
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/mat4x4.hpp> // glm::mat4
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/gtc/type_ptr.hpp> // glm::value_ptr

// Include SOIL
//#include "/usr/local/include/SOIL/SOIL.h"

class Camera;

class Shader
{
private:
    const char* vertex_shader;
    const char* fragment_shader;

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLint ModelTransform;
    GLint ProjectionMatrix;
    GLint ViewMatrix;
    GLint CamPos;
    GLuint uniformID;

    void compileShader();

public:
    int type;
    Camera *camera;
    Shader(int type, Camera* camera);
    void setShader(glm::mat4 M);
};


#endif //ZPG_TEST_SHADER_H
