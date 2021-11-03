//
// Created by Jan Mikulenka on 25.10.2021.
//

#ifndef ZPG_TEST_SCENE_H
#define ZPG_TEST_SCENE_H

#include "Storage.h"

class Scene {

private:
    Storage *storage;
public:
    Scene();
    void addObject(Object *obj);
    void remoceObject(int number);
    Object* getObject(int number);
    int getNumberOfObjects();
};


#endif //ZPG_TEST_SCENE_H
