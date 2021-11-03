//
// Created by Jan Mikulenka on 25.10.2021.
//

#ifndef ZPG_TEST_OBJECT_H
#define ZPG_TEST_OBJECT_H

#include "Model.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"

class Object {

private:
    Model *model;
    Transform *transform;
    Shader *shader;

public:
    Object(std::vector<float> pnts);
    void Draw(keyPress *keyScan);
    void addTransform(transStruct t);
    void removeTransform (transStruct t);
    void calculateTransform();
};


#endif //ZPG_TEST_OBJECT_H
