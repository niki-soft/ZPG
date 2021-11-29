//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Scene.h"

Scene::Scene() {
    storage = new Storage();
}

void Scene::addObject(Object *obj) {
    this->storage->addObject(obj);
}

void Scene::removeObject(int number) {
    this->storage->removeObject(number);
}

Object* Scene::getObject(int number) {
    return this->storage->getObject(number);
}

int Scene::getNumberOfObjects() {
    return this->storage->getNumberOfObjects();
}