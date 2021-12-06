//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Object.h"
#include "Camera.h"

Object::Object(std::vector<float> pnts, Shader* sh) {

    if (sh->textureUnit == nullptr)
    {
        this->model = new Model(pnts);
    }
    else
    {
        this->model = new TexturedModel(pnts);
    }

    this->shader = sh;
    this->transform = new Transform();
}

void Object::Draw(keyPress *keyScan) {
    this->shader->camera->Inputs(keyScan);
    this->transform->calculateTransform();
    this->shader->setShader(this->transform->M);
    this->model->setVAO();

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

void Object::changeShader(Shader *sh) {
  this->shader = sh;
}
