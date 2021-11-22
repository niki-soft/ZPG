//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h> 

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>

#include <SOIL.h>

#include <iostream>


float points[] = {
0.000000f, -0.500000f, 0.500000f, -0.872900f, 0.218200f, 0.436400f, 0.836598f, 0.477063f,
0.000000f, 0.500000f, 0.000000f, -0.872900f, 0.218200f, 0.436400f, 0.399527f, 0.286309f,
-0.500000f, -0.500000f, -0.500000f, -0.872900f, 0.218200f, 0.436400f, 0.836598f, 0.000179f,
-0.500000f, -0.500000f, -0.500000f, 0.000000f, -1.000000f, 0.000000f, 0.381686f, 0.999821f,
0.500000f, -0.500000f, -0.500000f, 0.000000f, -1.000000f, 0.000000f, 0.000179f, 0.809067f,
0.000000f, -0.500000f, 0.500000f, 0.000000f, -1.000000f, 0.000000f, 0.381686f, 0.522937f,
0.500000f, -0.500000f, -0.500000f, 0.872900f, 0.218200f, 0.436400f, 0.399169f, 0.000179f,
0.000000f, 0.500000f, 0.000000f, 0.872900f, 0.218200f, 0.436400f, 0.399169f, 0.522579f,
0.000000f, -0.500000f, 0.500000f, 0.872900f, 0.218200f, 0.436400f, 0.000179f, 0.261379f,
-0.500000f, -0.500000f, -0.500000f, 0.000000f, 0.447200f, -0.894400f, 0.788901f, 0.477421f,
0.000000f, 0.500000f, 0.000000f, 0.000000f, 0.447200f, -0.894400f, 0.788901f, 0.999821f,
0.500000f, -0.500000f, -0.500000f, 0.000000f, 0.447200f, -0.894400f, 0.399527f, 0.651554f
};

const char* vertex_shader =
"#version 330\n"
"layout(location = 0) in vec3 vp;"
"layout(location = 1) in vec3 vc;"
"layout(location = 2) in vec2 uv; "
"uniform mat4 modelMatrix;"
"out vec2 uvc;"
    ""
"void main () {"
"    gl_Position = modelMatrix * vec4 (vp, 1.0);"
"    uvc=uv;"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"uniform sampler2D textureUnitID;"
"in vec2 uvc;"
"void main () {"
"     frag_colour = texture(textureUnitID, uvc);"
"}";


static void error_callback(int error, const char* description) { 
    fputs(description, stderr); 
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();


    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);
    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //enable vertex attributes
    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 6));
    

    //create and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
    
    glActiveTexture(GL_TEXTURE0);
    GLuint image = SOIL_load_OGL_texture("wooden_fence.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (image == NULL) {
        std::cout << "An error occurred while loading image." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, image);

    glm::mat4 M = glm::mat4(1.0f);
    float angle = 0;
    


    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        M = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 1.0f, 1.0f));
        GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
        glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);

        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 12); //mode,first,count
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
        angle += 0.01f;
    }
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}