//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Shader.h"
#include "Camera.h"
#include <iostream>
Shader::Shader(Camera *cam, const char* vertexFile, const char* fragmentFile, int textureUnit) {
    this->textureUnit = new int;
    this->camera = cam;
    *this->textureUnit = textureUnit;
    compileShader(vertexFile, fragmentFile);
}

Shader::Shader(Camera *cam, const char* vertexFile, const char* fragmentFile) {

    this->camera = cam;
    this->textureUnit = nullptr;
    compileShader(vertexFile, fragmentFile);
}

void Shader::compileShader(const char* vertexFile, const char* fragmentFile) {

    ShaderLoader* shld = new ShaderLoader();
    shaderProgram = shld->loadShader(vertexFile, fragmentFile);
    delete(shld);

    ModelTransform = glGetUniformLocation(shaderProgram, "ModelMatrix");
    ProjectionMatrix = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
    ViewMatrix = glGetUniformLocation(shaderProgram, "ViewMatrix");
    CamPos = glGetUniformLocation(shaderProgram, "CamPosition");

    uniformID = glGetUniformLocation(shaderProgram, "textureUnitID");

}
void Shader::setShader(glm::mat4 M) {

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(ModelTransform, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(ProjectionMatrix, 1, GL_FALSE, glm::value_ptr(camera->projection));
    glUniformMatrix4fv(ViewMatrix, 1, GL_FALSE, glm::value_ptr(camera->view));
    glUniform3fv(CamPos, 1, &this->camera->Position[0]);

    if (this->textureUnit != nullptr && *this->textureUnit !=-1)
        glUniform1i(uniformID, *this->textureUnit);
    /*
    if (this->type == 2) {
        glUniform1i(uniformID, 0); //texture unit 0
        //std::cout << "Texture unit 0 set" << std::endl;
    }

    if (this->type == 3)
        glUniform1i(uniformID, 1); //texture unit 1
    */
}