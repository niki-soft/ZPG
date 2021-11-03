//
// Created by Jan Mikulenka on 25.10.2021.
//

#ifndef ZPG_TEST_STORAGE_H
#define ZPG_TEST_STORAGE_H

#include <vector>
#include "Object.h"


class Storage {
private:
    std::vector<Object*> objects;

public:
    Storage();
    Object* getObject(int number);
    void addObject(Object* o);
    void removeObject(int number);
    int getNumberOfObjects();
};


#endif //ZPG_TEST_STORAGE_H
