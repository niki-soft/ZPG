//
// Created by Jan Mikulenka on 27.10.2021.
//

#include "ObjectFactory.h"

ObjectFactory::ObjectFactory() {
    points = {
                -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                0.0f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
                0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f
    };
}