//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Shader.h"
#include "Camera.h"

Shader::Shader(Camera *cam) {

    this->camera = cam;

    this->vertex_shader =
            "#version 400\n"
            "layout(location=0) in vec3 vp;"
            "layout(location=1) in vec3 normal;"
            "uniform mat4 ModelMatrix;"
            "uniform mat4 ProjectionMatrix;"
            "uniform mat4 ViewMatrix;"
            "uniform vec3 CamPosition;"
            "out vec3 Normals;"
            "out vec3 FragPos;"
            "out vec3 CamPos;"
            "void main () {"
            "     gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4 (vp, 1.0);"
            "     vec4 a = ModelMatrix * vec4(vp, 1.0f);"
            "     FragPos = a.xyz / a.w;"
            "     Normals=transpose(inverse(mat3(ModelMatrix))) * normal;"
            "     CamPos = CamPosition;"
            "}";

    this->fragment_shader =
            "#version 400\n"
            "in vec3 Normals;"
            "in vec3 FragPos;"
            "in vec3 CamPos;"
            "out vec4 FragColor;"

            "void main () {"
            "   vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);"
            "   vec3 lightVector = normalize(lightPos - FragPos);"
            "   float dot_product = max(dot(normalize(lightVector), normalize(Normals)), 0.0);"
            "   vec4 diffuse = dot_product * vec4(0.385f, 0.647f, 0.812f, 1.0f);"
            "   vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
            "   float specularStrength = 0.75;"
            "   vec3 viewDir = normalize(CamPos - FragPos);"
            "   vec3 reflectDir = reflect(-lightVector, Normals);"
            "   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);"
            "   vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f);"
            "   FragColor = ambient+diffuse + vec4(specular, 1.0f);"
            "}";

            compileShader();
    /*
    this->vertex_shader =
            "#version 330\n"
            "layout(location=0) in vec3 vp;"
            "layout(location=1) in vec3 normal;"
            "uniform mat4 ModelMatrix;"
            "uniform mat4 CameraMatrix;"
            "out vec3 Normals;"
            "out vec4 FragPosition;"
            "void main () {"
            "     gl_Position = CameraMatrix * ModelMatrix * vec4 (vp, 1.0);"
            "     Normals=normal;"
            "     FragPosition = ModelMatrix * vec4(vp, 1.0);"
            "}";

    this->fragment_shader =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 Normals;"
            "in vec3 FragPosition;"

            "void main () {"
            "float amb = 0.1;"
            "     frag_colour = amb * vec4(Normals, 1.0f);"
            "}";

*/
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
    CamPosition = glGetUniformLocation(shaderProgram, "CamPosition");
    glUseProgram(shaderProgram);
}
void Shader::setShader(glm::mat4 M) {

    glUniformMatrix4fv(ModelTransform, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(ProjectionMatrix, 1, GL_FALSE, glm::value_ptr(camera->projection));
    glUniformMatrix4fv(ViewMatrix, 1, GL_FALSE, glm::value_ptr(camera->view));
    glUniform3f(CamPosition, 1, GL_FALSE, this->camera->Position[0]);

}