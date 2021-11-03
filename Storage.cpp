//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Storage.h"

Storage::Storage() {

}

Object* Storage::getObject(int number) {
    return objects[number];
}

void Storage::addObject(Object* o) {
    this->objects.push_back(o);
}

void Storage::removeObject(int number) {
    this->objects.erase(this->objects.begin()+number);
}
int Storage::getNumberOfObjects() {
    return objects.size();
}