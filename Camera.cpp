//
// Created by Jan Mikulenka on 30.10.2021.
//

#include "Camera.h"
#include "Shader.h"
#include <iostream>


Camera::Camera(int width, int height, glm::vec3 position) {

    Camera::width = width;
    Camera::height = height;
    Camera::Position = position;
    //Camera::shaders.push_back(shader);
    Camera::Matrix(45.0f, 0.01f, 100.0f);

}
 void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane) {


     this->projection = glm::perspective(FOVdeg, (float) ((float)width/(float)height), nearPlane, farPlane);
     this->view = glm::lookAt(Position, Position + Orientation, Up);

/*
     this->projection = glm::perspective(45.0f, 16.0f / 9.0f, 0.01f, 100.0f);
     this->view = glm::lookAt(
             glm::vec3(0, 0, 10), // Camera is at (4,3,-3), in World Space
             glm::vec3(0, 0, -1) + glm::vec3(0, 0, 10), // and looks at the origin
             glm::vec3(0, 1, 0));  // Head is up (set to 0,-1,0 to look upside-down)
 */
 }

void Camera::Inputs(keyPress *keyScan) {
    bool change = false;

    if (keyScan->mods == 1 || keyScan->mods == 3)
    {
        speed = 0.02f;
        change = true;
    }
    else
    {
        speed = 0.005f;
        change = true;
    }

    if (keyScan->key == GLFW_KEY_UP && keyScan->action > 0) {
        Position += speed * Orientation;
        change = true;
    }
    if (keyScan->key == GLFW_KEY_DOWN && keyScan->action > 0) {
        Position += speed * -Orientation;
        change = true;
    }
    if (keyScan->key == GLFW_KEY_LEFT && keyScan->action > 0) {
        Position += speed * -glm::normalize(glm::cross(Orientation, Up));

        change = true;
    }
    if (keyScan->key == GLFW_KEY_RIGHT && keyScan->action > 0) {
        Position += speed * glm::normalize(glm::cross(Orientation, Up));
        change = true;
    }


    if (keyScan->key == GLFW_KEY_SPACE && keyScan->action > 0)
    {
        Position += speed * Up;
        change = true;
    }

    if ( (keyScan->key == 341 && keyScan->mods == 2) || (keyScan->key == 340 && keyScan->mods == 3) || (keyScan->key == 340 && keyScan->mods == 2))
    {
        Position += speed * -Up;
        change = true;
    }


    if (keyScan->key == GLFW_KEY_LEFT_SHIFT  && keyScan->action > 0)
    {
        speed = 0.4f;
        change = true;

    }
    else if (keyScan->key == GLFW_KEY_LEFT_SHIFT && keyScan->action == 0)
    {
        speed = 0.1f;
        change = true;
    }

    if (keyScan->but_action == 0)
    {
        firstMouse = true;
        lastX = keyScan->x;
        lastY = keyScan->y;
    }

 /*
    if (keyScan->but_action == 1 && keyScan->button == 1)
    {

        const float radius = 10.0f;
        Orientation.x += sin(glfwGetTime()) * radius;
        Orientation.z += cos(glfwGetTime()) * radius;

        //std::cout << "Rotace" << " " << camX << "," << camZ << std::endl;

        //Orientation = glm::vec3(camX,0.0, camZ);
        //Orientation = glm::vec3(0.0, 0.0, 0.0);
        this->view = glm::lookAt(Position, Position + Orientation, Up);
    }
*/


    if (keyScan->but_action == 1 && keyScan->button == 1)
    {
        if (firstMouse)
        {
            lastX = keyScan->x;
            lastY = keyScan->y;
            firstMouse = false;
        }

        if (lastX == 0)
        {
            lastX = keyScan->x;
            lastY = keyScan->y;
        }

        float xoffset = keyScan->x - lastX;
        float yoffset = lastY - keyScan->y;

        lastX = keyScan->x;
        lastY = keyScan->y;
        xoffset *= 0.5f;
        yoffset *= 0.5f;


        yaw += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;


        //std::cout << pitch << "," << yaw << std::endl;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        Orientation = glm::normalize(direction);

        this->view = glm::lookAt(Position, Position + Orientation, Up);
    }

    if (change)
        cameraChanged();
}

void Camera::cameraChanged() {
    this->view = glm::lookAt(Position, Position + Orientation, Up);
}