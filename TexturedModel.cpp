//
// Created by Jan Mikulenka on 27.11.2021.
//

#include "TexturedModel.h"


TexturedModel::TexturedModel(std::vector<float> pnts, int typ) : Model(pnts, typ){

        points = new float[pnts.size()];
        std::copy(pnts.begin(), pnts.end(), points);

        triangle_count = (int)pnts.size()/8;

        initialize();
        std::cout << "Textured object created" << std::endl;
}

void TexturedModel::initialize()
{
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*triangle_count*8, points, GL_STATIC_DRAW);

    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO

    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1); //normal atribute
    glEnableVertexAttribArray(2); //texture atribute

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    std::cout << "Inicializace TextureModel konec" << std::endl;
}
