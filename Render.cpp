//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Render.h"
#include <vector>
#include "cube.h"
#include "tree.h"
#include "suzi_smooth.h"
#include "gift.h"
//#include "bushes.h"
#include "Camera.h"
#include "sphere.h"
#include "plain.h"
#include "building.h"
#include "skydome.h"
#include <iostream>

int actuallyScene = 1;

bool rightMouse = false;
int zn = 1;
int zn1 = 1;

std::vector<Shader*> shaders;

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

void Render::LoadTextures() {

    //cv::Mat img = cv::imread("test.png", 1);
    //cv::Mat img = cv::imread("wooden_fence.png", 1);
    cv::Mat img = cv::imread("fulldome3.jpg", 1);
    cv::flip(img, img, 0);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    img.release();
    cv::Mat newimg;
    newimg =cv::imread("floor2.png", 1);
    cv::flip(newimg, newimg, 0);
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, newimg.cols, newimg.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, newimg.ptr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    newimg.release();

}

Camera* Render::generateCamera() {
    return new Camera(1366, 768, glm::vec3(1.0f, 1.0f, 15.0f));
}

void Render::CreateNewObject(Shader* sh)
{
    std::cout << "Pokus o vygenerování nového objektu" << std::endl;

    Scene* sc = new Scene;

    sc = scenes[actuallyScene];

    sc->addObject(new Object(c, sh));
    glm::vec3 pos = sh->camera->Position;
    glm::vec3 ori = sh->camera->Orientation;
    sc->getObject(sc->getNumberOfObjects()-1)->addTransform({"translate", 1, pos});
    sc->getObject(sc->getNumberOfObjects()-1)->calculateTransform();
    sc->getObject(sc->getNumberOfObjects()-1)->removeTransform({"translate", 1, pos});
    sc->getObject(sc->getNumberOfObjects()-1)->
    addTransform({"translate", 1, glm::vec3(ori.x/5, ori.y/5, ori.z/5)});

    std::cout << "Nový objekt vygenerován" << std::endl;
}

// Callback
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
void Render::cursor_callback(GLFWwindow* window, double x, double y) {
    keyScan->x = x;
    keyScan->y = y;

    //std::cout << x << "," << y << std::endl;
}
void Render::button_callback(GLFWwindow* window, int button, int action, int mode) {


    keyScan->button = button;
    keyScan->but_action = action;
    keyScan->but_mode = mode;

    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
    if ( (button == 1 ) && (action==0) ) {
        if (!rightMouse) {
            zn = -1;
            zn1 = zn1 * -1;
            rightMouse = true;
        } else {
            rightMouse = false;
        }

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

void Render::InitScene(){
    Scene* sc = new Scene;
    sc = scenes[actuallyScene];

    if (actuallyScene==0) {
        sc->addObject(new Object(c, shaders[3]));
        sc->addObject(new Object(c, shaders[0]));
        sc->addObject(new Object(c, shaders[0]));
        sc->addObject(new Object(c, shaders[0]));
        sc->addObject(new Object(c, shaders[0]));
        sc->addObject(new Object(suziSmooth, shaders[0]));
        sc->addObject(new Object(tree, shaders[0]));
        sc->addObject(new Object(plain, shaders[2]));
        sc->addObject(new Object(sphere, shaders[0]));

        sc->addObject(new Object(skydome,shaders[1]));

        //Object *kostka = new Object(c);

        //scene1->getObject(0)->shader->setShader(scene1->getObject(0)->transform->M);
        //scene1->getObject(0)->addTransform({"rotate", 0.02f, glm::vec3(1.0f, 0.0f, 1.0f)});
        //scene1->getObject(0)->transform->addTransform({"scale", 0.985, glm::vec3(0.985) });
        sc->getObject(0)->addTransform({"translate", 1, glm::vec3(3, 0, 0)});
        sc->getObject(0)->calculateTransform();
        sc->getObject(0)->removeTransform({"translate", 1, glm::vec3(3, 0, 0)});

        //scene1->getObject(1)->shader->setShader(scene1->getObject(1)->transform->M);
        //scene1->getObject(1)->transform->addTransform({"scale", 0.4, glm::vec3(0.4) });
        sc->getObject(1)->addTransform({"translate", 1, glm::vec3(-3, 0, 0)});
        sc->getObject(1)->calculateTransform();
        //scene1->getObject(1)->transform->removeTransform({"scale", 0.4, glm::vec3(0.4) });
        sc->getObject(1)->removeTransform({"translate", 1, glm::vec3(-3, 0, 0)});

        //scene1->getObject(1)->addTransform( {"translate", 1,glm::vec3(-0.5, 0.0, 0.0)} );
        //scene1->getObject(1)->addTransform({"rotate", 0.02f, glm::vec3(1.0f, 0.0f, 1.0f)});
        //scene1->getObject(1)->addTransform( {"translate", 1,glm::vec3(0.5, -0.0, -0.0)} );
        //scene1->getObject(2)->shader->setShader(scene1->getObject(1)->transform->M);

        sc->getObject(2)->addTransform({"translate", 1, glm::vec3(0.0, -3.0, -0.0)});
        sc->getObject(2)->calculateTransform();
        sc->getObject(2)->removeTransform({"translate", 1, glm::vec3(0.0, -3.0, -0.0)});
        //scene1->getObject(2)->addTransform( {"translate", 1,glm::vec3(0.0, -0.5, 0.0)} );
        //scene1->getObject(2)->addTransform({"rotate", 0.02f, glm::vec3(1.0f, 0.0f, 1.0f)});
        //scene1->getObject(2)->addTransform( {"translate", 1,glm::vec3(0.0, 0.5, -0.0)} );

        //scene1->getObject(0)->model->setVAO();
        //scene1->getObject(1)->model->setVAO();
        //scene1->getObject(2)->model->setVAO();

        sc->getObject(3)->addTransform({"translate", 1, glm::vec3(0.0, 3.0, -0.0)});
        sc->getObject(3)->calculateTransform();
        sc->getObject(3)->removeTransform({"translate", 1, glm::vec3(0.0, 3.0, -0.0)});

        //scene1->getObject(4)->addTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
        sc->getObject(4)->addTransform({"translate", 1, glm::vec3(-6.0, -0.5, -0.0)});
        sc->getObject(4)->calculateTransform();
        //scene1->getObject(4)->removeTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
        sc->getObject(4)->removeTransform({"translate", 1, glm::vec3(-6.0, -0.5, -0.0)});
        sc->getObject(4)->addTransform({"rotate", 0.001f, glm::vec3(0.0f, 1.0f, 0.0f)});


        //scene1->getObject(5)->addTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
        sc->getObject(5)->addTransform({"translate", 1, glm::vec3(2.0, 2.0, -0.0)});
        sc->getObject(5)->calculateTransform();
        sc->getObject(5)->removeTransform({"translate", 1, glm::vec3(2.0, 2.0, -0.0)});
        sc->getObject(5)->addTransform({"rotate", 0.001f, glm::vec3(0.0f, 1.0f, 0.0f)});

        //scene1->getObject(5)->addTransform({"rotate", 0.1f, glm::vec3(0.0f, 1.0f, 0.0f)});

        //scene1->getObject(6)->addTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
        sc->getObject(6)->addTransform({"translate", 1, glm::vec3(10.0, -0.5, -50.0)});
        sc->getObject(6)->calculateTransform();
        //scene1->getObject(6)->removeTransform({"rotate", 3.14f, glm::vec3(0.0f, 0.0f, 1.0f)});
        sc->getObject(6)->removeTransform({"translate", 1, glm::vec3(10.0, -0.5, -50.0)});
        sc->getObject(6)->addTransform({"rotate", -0.001f, glm::vec3(0.0f, 1.0f, 0.0f)});

        //Plain
        sc->getObject(7)->addTransform({"translate", 1, glm::vec3(0.0, 0.0, 0.0)});
        sc->getObject(7)->addTransform({"scale", 1 ,glm::vec3(60.0f, 0.0f, 60.0f)});
        sc->getObject(7)->calculateTransform();
        sc->getObject(7)->removeTransform({"translate", 1, glm::vec3(0.0, 0.0, 0.0)});
        sc->getObject(7)->removeTransform({"scale", 1, glm::vec3(60.0f, 0.0f, 60.0f)});

        //koule
        sc->getObject(8)->addTransform({"translate", 1, glm::vec3(0.0, 0.0, -10.0)});
        sc->getObject(8)->calculateTransform();
        sc->getObject(8)->removeTransform({"translate", 1, glm::vec3(0.0, 0.0, -10.0)});
        //scene1->getObject(8)->addTransform({"rotate", -0.02f, glm::vec3(0.0f, 1.0f, 0.0f)});

        //Skydome
        sc->getObject(9)->addTransform({"scale", 1 ,glm::vec3(8.0f, 10.0f, 8.0f)});
        sc->getObject(9)->calculateTransform();
        sc->getObject(9)->removeTransform({"scale", 1, glm::vec3(8.0f, 10.0f, 8.0f)});
    }
    else if (actuallyScene == 1)
    {
        sc->addObject(new Object(sphere,shaders[0]));
        sc->addObject(new Object(sphere,shaders[0]));
        sc->addObject(new Object(sphere,shaders[3]));
        sc->addObject(new Object(sphere,shaders[0]));

       sc->addObject(new Object(plain,shaders[2]));
        sc->addObject(new Object(skydome,shaders[1]));

        sc->getObject(0)->addTransform({"translate", 1,glm::vec3(-3, 0, 0)});
        sc->getObject(0)->calculateTransform();

        sc->getObject(0)->removeTransform({"translate", 1,glm::vec3(-3, 0, 0)});

        sc->getObject(1)->addTransform({"translate", 1,glm::vec3(3, 0, 0)});
        sc->getObject(1)->calculateTransform();
        sc->getObject(1)->removeTransform({"translate", 1,glm::vec3(3, 0, 0)});

        sc->getObject(2)->addTransform({"translate", 1,glm::vec3(0, 3, 0)});
        sc->getObject(2)->calculateTransform();
        sc->getObject(2)->removeTransform({"translate", 1,glm::vec3(0, 3, 0)});

        sc->getObject(3)->addTransform({"translate", 1,glm::vec3(0, -3, 0)});
        sc->getObject(3)->calculateTransform();
        sc->getObject(3)->removeTransform({"translate", 1,glm::vec3(0, -3, 0)});

        sc->getObject(4)->addTransform({"scale", 1 ,glm::vec3(30.0f, 0.0f, 30.0f)});
        sc->getObject(4)->calculateTransform();
        sc->getObject(4)->removeTransform({"scale", 1, glm::vec3(30.0f, 0.0f, 30.0f)});

        sc->getObject(5)->addTransform({"scale", 1 ,glm::vec3(10.0f, 10.0f, 10.0f)});
        sc->getObject(5)->calculateTransform();
        sc->getObject(5)->removeTransform({"scale", 1, glm::vec3(10.0f, 10.0f, 10.0f)});

    }
    else if (actuallyScene == 2){
        sc->addObject(new Object(building,shaders[2]));
    }

}

Render::Render() {
};

void Render::RenderView() {

    for (int i =0; i<5; i++)
    {
        scenes.push_back(new Scene);
    }

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

    LoadTextures();     // Nahrání textur

    Camera* cam = generateCamera(); // Vygenerování kamery

    Shader* sh = new Shader(cam, "../Shaders/shader1.vs", "../Shaders/shader1.fs");  // Normální model

    //sh = loadShader("/Shaders/shader1.vs", "/Shaders/shader1.fs")
    shaders.push_back(sh);

    sh = NULL;
    sh = new Shader(cam, "../Shaders/shader2.vs", "../Shaders/shader2.fs", 0);        // Texturovaný model - texturovací jednotka 0;
    shaders.push_back(sh);

    sh = NULL;
    sh = new Shader(cam, "../Shaders/shader2.vs", "../Shaders/shader2.fs", 1);        // Texturovaný model - texturovací jednotka 1
    shaders.push_back(sh);

    sh = NULL;
    sh = new Shader(cam, "../Shaders/shader3.vs", "../Shaders/shader3.fs");        // Normálmní model - červený
    shaders.push_back(sh);

    InitScene();        //Inicializace scény

    glEnable(GL_DEPTH_TEST);

    std::vector<int> objectsToDelete;
    bool firstclick = false;
    while (!glfwWindowShouldClose(window)){

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (keyScan->button == 0 && keyScan->but_action == 0 && firstclick)
            firstclick = false;

        if (keyScan->button == 0 && keyScan->but_action == 1 && !firstclick) {
            std::cout << "Button pressed" << std::endl;
            CreateNewObject(shaders[0]);
            firstclick = true;
            scenes[actuallyScene]->getObject(0)->changeShader(shaders[3]);
        }

        for (int i = 0; i < scenes[actuallyScene]->getNumberOfObjects(); i++) {
            scenes[actuallyScene]->getObject(i)->Draw(keyScan);
            if (i == scenes[actuallyScene]->getNumberOfObjects() - 1)
            {
                //std::cout << "Object " << i << " má z souřadnici" << scenes[actuallyScene]->getObject(i)->getZetPosition() << std::endl;
            }
         }

        for (int i = 0; i < scenes[actuallyScene]->getNumberOfObjects(); i++) {
            if (scenes[actuallyScene]->getObject(i)->getZetPosition() < -100)
                objectsToDelete.push_back(i);
        }

        for (int i = 0; i < objectsToDelete.size(); i++) {
           //std::cout << "Budu mazat object č." << objectsToDelete[i] << std::endl;

           scenes[actuallyScene]->removeObject(objectsToDelete[i]);
        }

        objectsToDelete.clear();

        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}