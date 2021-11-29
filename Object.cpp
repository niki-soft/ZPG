//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Object.h"
#include "Camera.h"

Object::Object(std::vector<float> pnts, Shader* sh) {

    if (sh->type == 1){
        this->model = new Model(pnts);
    }

    if (sh->type == 2 || sh->type == 3) {
        this->model = new TexturedModel(pnts);
    }

    this->shader = sh;
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
float Object::getZetPosition() {
    return this->transform->M[3][2];
}
