//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Shader.h"
#include "Camera.h"

Shader::Shader(Camera *cam) {

    this->camera = cam;

    this->vertex_shader =
            "#version 330\n"
            "layout(location=0) in vec3 vp;"
            "layout(location=1) in vec3 color;"
            "uniform mat4 ModelMatrix;"
            "uniform mat4 CameraMatrix;"
            "out vec3 barva;"
            "void main () {"
            "     gl_Position = CameraMatrix * ModelMatrix * vec4 (vp, 1.0);"
            "     barva=color;"
            "}";

    this->fragment_shader =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 barva;"
            "void main () {"
            "     frag_colour = vec4 (0.5, 1.0, 0.5, 1.0);"
            "     frag_colour = vec4(barva, 1.0);"
            "}";

}

void Shader::setShader(glm::mat4 M) {

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    ModelTransform = glGetUniformLocation(shaderProgram, "ModelMatrix");
    CameraMatrix = glGetUniformLocation(shaderProgram, "CameraMatrix");
    //Projection = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
    //View = glGetUniformLocation(shaderProgram, "ViewMatrix");

    glUseProgram(shaderProgram);

    glUniformMatrix4fv(ModelTransform, 1, GL_FALSE, &M[0][0]);
    //camera->Matrix(45.0f, 0.01f, 100.0f, shaderProgram, "camMatrix" );
    glUniformMatrix4fv(CameraMatrix, 1, GL_FALSE, glm::value_ptr(camera->projection * camera->view));
    //glUniformMatrix4fv(Projection, 1, GL_FALSE, &camera->projection[0][0]);
    //glUniformMatrix4fv(View, 1, GL_FALSE, &camera->view[0][0]);

    //glUniformMatrix4fv(Projection, 1, GL_FALSE, &camera.ProjectionMat[0][0]);
    //glUniformMatrix4fv(View, 1, GL_FALSE, &camera->ViewMat[0][0]);


}