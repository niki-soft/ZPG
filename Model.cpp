//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Model.h"
#include <iostream>

Model::Model(std::vector<float> pnts) {


    number = 6;

    points = new float[pnts.size()];
    std::copy(pnts.begin(), pnts.end(), points);

    triangle_count = (int)pnts.size()/number;
    initialize();
    //std::cout << "Normalní objekt vygenerován." << std::endl;
}

void Model::initialize() {

    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*triangle_count*number, points, GL_STATIC_DRAW);

    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO

    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1); //normal atribute
/*
    if (number > 6)
        glEnableVertexAttribArray(2); //texture atribute
*/
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, number * sizeof(GL_FLOAT), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, number * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
/*
    if (number > 6)
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
*/
    //std::cout << "Inicializace Model konec" << std::endl;
}

void Model::setVAO() {
    glBindVertexArray(this->VAO);
}

int Model::numberOfTriangles() {
    return this->triangle_count;
}