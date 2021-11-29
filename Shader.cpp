//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Shader.h"
#include "Camera.h"
#include <iostream>
Shader::Shader(int typ, Camera *cam) {

    this->camera = cam;
    this->type = typ;
    if (this->type == 1) {
        this->vertex_shader =
                "#version 400\n"
                "layout(location=0) in vec3 vp;"
                "layout(location=1) in vec3 normal;"
                "uniform mat4 ModelMatrix;"
                "uniform mat4 ProjectionMatrix;"
                "uniform mat4 ViewMatrix;"
                "out vec3 Normals;"
                "out vec3 FragPos;"
                "void main () {"
                "     gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4 (vp, 1.0);"
                "     vec4 a = ModelMatrix * vec4(vp, 1.0f);"
                "     FragPos = a.xyz / a.w;"
                "     Normals = transpose(inverse(mat3(ModelMatrix))) * normal;"
                "}";

        this->fragment_shader =
                "#version 400\n"
                "in vec3 Normals;"
                "in vec3 FragPos;"
                "uniform vec3 CamPosition;"
                "out vec4 FragColor;"

                "void main () {"
                "   vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);"
                "   vec3 lightVector = lightPos - FragPos;"
                "   float dot_product = max(dot(normalize(lightVector), normalize(Normals)), 0.0);"
                "   vec4 diffuse = dot_product * vec4(0.385f, 0.647f, 0.812f, 1.0f);"
                "   vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
                "   float specularStrength = 0.75;"
                "   vec3 viewDir = normalize(CamPosition - FragPos);"
                "   vec3 reflectDir = reflect(-lightVector, Normals);"
                "   float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), 16);"
                "   vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f);"
                "   FragColor = ambient+diffuse + vec4(specular, 1.0f);"
                "}";
    }

    if (this->type >= 2) {
        this->vertex_shader =
                "#version 400\n"
                "layout(location=0) in vec3 vp;"
                "layout(location=1) in vec3 normal;"
                "layout(location=2) in vec2 aTexCoord;"
                "uniform mat4 ModelMatrix;"
                "uniform mat4 ProjectionMatrix;"
                "uniform mat4 ViewMatrix;"
                "out vec3 Normals;"
                "out vec3 FragPos;"
                "out vec2 TexCoord;"
                "void main () {"
                "     gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4 (vp, 1.0);"
                "     vec4 a = ModelMatrix * vec4(vp, 1.0f);"
                "     FragPos = a.xyz / a.w;"
                "     Normals = transpose(inverse(mat3(ModelMatrix))) * normal;"
                "     TexCoord = aTexCoord;"
                "}";

        this->fragment_shader =
                "#version 400\n"
                "in vec3 Normals;"
                "in vec3 FragPos;"
                "uniform vec3 CamPosition;"
                "out vec4 FragColor;"
                "uniform sampler2D textureUnitID;"
                "in vec2 TexCoord;"
                "void main () {"
                "   vec3 lightPos = vec3(0.0f, 20.0f, 20.0f);"
                "   vec3 lightVector = lightPos - FragPos;"
                "   float dot_product = max(dot(normalize(lightVector), normalize(Normals)), 0.0);"
                "   vec4 diffuse = dot_product * vec4(0.385f, 0.647f, 0.812f, 1.0f);"
                "   vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
                "   float specularStrength = 0.75;"
                "   vec3 viewDir = normalize(CamPosition - FragPos);"
                "   vec3 reflectDir = reflect(-lightVector, Normals);"
                "   float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), 16);"
                "   vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f);"
                "   FragColor = ambient+diffuse + vec4(specular, 1.0f);"
                "   FragColor = texture(textureUnitID, TexCoord);"
                "}";
    }
    compileShader();

}
void Shader::compileShader() {
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
    ProjectionMatrix = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
    ViewMatrix = glGetUniformLocation(shaderProgram, "ViewMatrix");
    CamPos = glGetUniformLocation(shaderProgram, "CamPosition");

    if (this->type >= 2)
        uniformID = glGetUniformLocation(shaderProgram, "textureUnitID");

}
void Shader::setShader(glm::mat4 M) {

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(ModelTransform, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(ProjectionMatrix, 1, GL_FALSE, glm::value_ptr(camera->projection));
    glUniformMatrix4fv(ViewMatrix, 1, GL_FALSE, glm::value_ptr(camera->view));
    glUniform3fv(CamPos, 1, &this->camera->Position[0]);

    if (this->type == 2) {
        glUniform1i(uniformID, 0); //texture unit 0
        //std::cout << "Texture unit 0 set" << std::endl;
    }

    if (this->type == 3)
        glUniform1i(uniformID, 1); //texture unit 1
}