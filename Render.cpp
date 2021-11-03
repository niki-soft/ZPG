//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Render.h"
#include <vector>
#include "Scene.h"
#include "cube.h"
#include "tree.h"
#include "suzi_smooth.h"
#include "gift.h"
#include "bushes.h"
#include "Camera.h"

bool rightMouse = false;
int zn = 1;
int zn1 = 1;
keyPress *keyScan = new keyPress();


Render* Render::instance = 0;
Render* Render::getInstance()
{
    if (!instance)
    {
        instance = new Render();
    }

    return instance;
}


void Render::error_callback(int error, const char* description) { fputs(description, stderr); }



void Render::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{


    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    keyScan->key = key;
    keyScan->scancode = scancode;
    keyScan->action = action;
    keyScan->mods = mods;



    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Render::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }
void Render::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }
void Render::window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}
void Render::cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }
void Render::button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
    if (button == 1)
        if (!rightMouse)
        {
            zn = -1;
            zn1 = zn1 * -1;
            rightMouse = true;
        }
        else
        {
            rightMouse = false;
        }

    if (button == 0)
    {
        zn = 1;
    }

}

void Render::GLMtest()
{
    //GLM test

    // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    //glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

    // Camera matrix
    //glm::mat4 View =

    // Model matrix : an identity matrix (model will be at the origin)
    //glm::mat4 Model = glm::mat4(1.0f);
}

Render::Render() {
};

void Render::RenderView() {

    //glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(1366, 768, "ZPG", NULL, NULL);
    if (!window)
    {
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

    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Sets the key callback
    glfwSetKeyCallback(window, key_callback);

    glfwSetCursorPosCallback(window, cursor_callback);

    glfwSetMouseButtonCallback(window, button_callback);

    glfwSetWindowFocusCallback(window, window_focus_callback);

    glfwSetWindowIconifyCallback(window, window_iconify_callback);

    glfwSetWindowSizeCallback(window, window_size_callback);


    Scene *scene1 = new Scene();

    scene1->addObject(new Object(c));
    scene1->addObject(new Object(c));
    scene1->addObject(new Object(c));
    scene1->addObject(new Object(c));
    scene1->addObject(new Object(tree));
    scene1->addObject(new Object(suziSmooth));
    scene1->addObject(new Object(tree));
    scene1->addObject(new Object(plain));


    //Object *kostka = new Object(c);

    //scene1->getObject(0)->shader->setShader(scene1->getObject(0)->transform->M);
    //scene1->getObject(0)->addTransform({"rotate", 0.02f, glm::vec3(1.0f, 0.0f, 1.0f)});
    //scene1->getObject(0)->transform->addTransform({"scale", 0.985, glm::vec3(0.985) });
    scene1->getObject(0)->addTransform({"translate", 1,glm::vec3(3, 0, 0)});
    scene1->getObject(0)->calculateTransform();
    scene1->getObject(0)->removeTransform({"translate", 1,glm::vec3(3, 0, 0)});

    //scene1->getObject(1)->shader->setShader(scene1->getObject(1)->transform->M);
    //scene1->getObject(1)->transform->addTransform({"scale", 0.4, glm::vec3(0.4) });
    scene1->getObject(1)->addTransform({"translate", 1,glm::vec3(-3, 0, 0)});
    scene1->getObject(1)->calculateTransform();
    //scene1->getObject(1)->transform->removeTransform({"scale", 0.4, glm::vec3(0.4) });
    scene1->getObject(1)->removeTransform( {"translate", 1,glm::vec3(-3, 0, 0)} );

    //scene1->getObject(1)->addTransform( {"translate", 1,glm::vec3(-0.5, 0.0, 0.0)} );
    //scene1->getObject(1)->addTransform({"rotate", 0.02f, glm::vec3(1.0f, 0.0f, 1.0f)});
    //scene1->getObject(1)->addTransform( {"translate", 1,glm::vec3(0.5, -0.0, -0.0)} );
    //scene1->getObject(2)->shader->setShader(scene1->getObject(1)->transform->M);

    scene1->getObject(2)->addTransform({"translate", 1,glm::vec3(0.0, -3.0, -0.0)});
    scene1->getObject(2)->calculateTransform();
    scene1->getObject(2)->removeTransform({"translate", 1,glm::vec3(0.0, -3.0, -0.0)});

    //scene1->getObject(2)->addTransform( {"translate", 1,glm::vec3(0.0, -0.5, 0.0)} );
    //scene1->getObject(2)->addTransform({"rotate", 0.02f, glm::vec3(1.0f, 0.0f, 1.0f)});
    //scene1->getObject(2)->addTransform( {"translate", 1,glm::vec3(0.0, 0.5, -0.0)} );

    //scene1->getObject(0)->model->setVAO();
    //scene1->getObject(1)->model->setVAO();
    //scene1->getObject(2)->model->setVAO();

    scene1->getObject(3)->addTransform({"translate", 1,glm::vec3(0.0, 3.0, -0.0)});
    scene1->getObject(3)->calculateTransform();
    scene1->getObject(3)->removeTransform({"translate", 1,glm::vec3(0.0, 3.0, -0.0)});

    //scene1->getObject(4)->addTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
    scene1->getObject(4)->addTransform({"translate", 1,glm::vec3(-6.0, -3.0, -0.0)});
    scene1->getObject(4)->calculateTransform();
    //scene1->getObject(4)->removeTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
    scene1->getObject(4)->removeTransform({"translate", 1,glm::vec3(-6.0, -3.0, -0.0)});
    scene1->getObject(4)->addTransform({"rotate", 0.02f, glm::vec3(0.0f, 1.0f, 0.0f)});


    //scene1->getObject(5)->addTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
    scene1->getObject(5)->addTransform({"translate", 1,glm::vec3(2.0, 2.0, -0.0)});
    scene1->getObject(5)->calculateTransform();
    scene1->getObject(5)->removeTransform({"translate", 1,glm::vec3(2.0, 2.0, -0.0)});
    //scene1->getObject(5)->removeTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});

    scene1->getObject(5)->addTransform({"rotate", 0.1f, glm::vec3(0.0f, 1.0f, 0.0f)});

    //scene1->getObject(6)->addTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
    scene1->getObject(6)->addTransform({"translate", 1,glm::vec3(10.0, -3.0, -50.0)});
    scene1->getObject(6)->calculateTransform();
    //scene1->getObject(6)->removeTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
    scene1->getObject(6)->removeTransform({"translate", 1,glm::vec3(10.0, -3.0, -50.0)});
    scene1->getObject(6)->addTransform({"rotate", -0.02f, glm::vec3(0.0f, 1.0f, 0.0f)});

    //scene1->getObject(7)->addTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
    scene1->getObject(7)->addTransform({"translate", 1,glm::vec3(0.0, 0.0, 0.0)});
    scene1->getObject(7)->calculateTransform();
    //scene1->getObject(7)->removeTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
    scene1->getObject(7)->removeTransform({"translate", 1,glm::vec3(0.0, 0.0, 0.0)});
    //scene1->getObject(6)->addTransform({"rotate", -0.02f, glm::vec3(0.0f, 1.0f, 0.0f)});
    int pocitadlo = 0;
    float meritko;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)){


        pocitadlo = pocitadlo + 1;
/*
        if ((pocitadlo > 200))
        {
            if (zn > 0)
            {
                scene1->getObject(0)->transform->removeTransform({"scale", 0.985, glm::vec3(0.985)});
                scene1->getObject(0)->transform->addTransform({"scale", 1.015, glm::vec3(1.015)});
            }
            else
            {
                scene1->getObject(0)->transform->removeTransform({"scale", 1.015, glm::vec3(1.015)});
                scene1->getObject(0)->transform->addTransform({"scale", 0.985, glm::vec3(0.985)});
            }
            zn = zn * -1;
            pocitadlo = 0;
        }
*/
        meritko = 1.0f - zn * 0.015;
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = 0; i < scene1->getNumberOfObjects(); i++) {
            scene1->getObject(i)->Draw(keyScan);

        }
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}