//
// Created by Jan Mikulenka on 27.10.2021.
//

#ifndef ZPG_GAME_OBJECTFACTORY_H
#define ZPG_GAME_OBJECTFACTORY_H

#include "Model.h"
#include <vector>

class ObjectFactory {
private:
    std::vector<float> points;
public:
    ObjectFactory();
    Model* MakeModel(char** m);

};


#endif //ZPG_GAME_OBJECTFACTORY_H
