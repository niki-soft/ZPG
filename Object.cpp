//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Object.h"
#include "Camera.h"

Object::Object(std::vector<float> pnts) {

    this->model = new Model(pnts);
    this->shader = new Shader(new Camera(this->shader, 1366, 768, glm::vec3(0.0f, 0.0f, 10.0f)));
    this->transform = new Transform();

}

void Object::Draw(keyPress *keyScan) {
    this->shader->camera->Inputs(keyScan);
    this->shader->setShader(this->transform->M);
    this->model->setVAO();
    this->transform->calculateTransform();
    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, this->model->numberOfTriangles()); //mode,first,count

};

void Object::addTransform(transStruct t) {
    this->transform->addTransform(t);
}

void Object::removeTransform(transStruct t) {
    this->transform->removeTransform(t);
}

void Object::calculateTransform() {
    this->transform->calculateTransform();
}