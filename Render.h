//
// Created by Jan Mikulenka on 25.10.2021.
//

#ifndef ZPG_TEST_RENDER_H
#define ZPG_TEST_RENDER_H

#include </usr/local/Cellar/glew/2.2.0_1/include/GL/glew.h> // include GLEW and new version of GL on Windows
#include </usr/local/Cellar/glfw/3.3.4/include/GLFW/glfw3.h>

//Include GLM
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/glm.hpp>
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/vec3.hpp> // glm::vec3
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/vec4.hpp> // glm::vec4
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/mat4x4.hpp> // glm::mat4
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include </usr/local/Cellar/glm/0.9.9.8/include/glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>
#include "Storage.h"
#include <vector>

class Render
{
private:

    int major, minor, revision;
    int width, height;
    float ratio = width / (float)height;

    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_focus_callback(GLFWwindow* window, int focused);
    static void window_iconify_callback(GLFWwindow* window, int iconified);
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void cursor_callback(GLFWwindow* window, double x, double y);
    static void button_callback(GLFWwindow* window, int button, int action, int mode);

    void GLMtest();
    static Render* instance;

    Render();

public:

    static Render* getInstance();
    void RenderView();
};


#endif //ZPG_TEST_RENDER_H
