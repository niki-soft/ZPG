//
// Created by Jan Mikulenka on 25.10.2021.
//

#include "Transform.h"

Transform::Transform() {
    this->M = glm::mat4(1.0f) ;
}

void Transform::calculateTransform() {
    for (auto i:this->trans)
    {
        if (i.text == "rotate" )
            this->M = glm::rotate(this->M, i.number, i.vct);

        if (i.text == "translate")
            this->M = glm::translate(this->M, i.vct*i.number);

        if (i.text == "scale")
            this->M = glm::scale(this->M, i.vct);

        if (i.text == "move") {
            this->M = glm::mat4(1.0f);
            this->M = glm::translate(this->M, i.vct*i.number);
        }

    } // End of for
}

void Transform::addTransform(transStruct t) {
    this->trans.push_back(t);
}

void Transform::removeTransform(transStruct t) {
    int remove = -1;
    for (int i = 0; i<this->trans.size(); i++)
    {
        if ( (t.text == this->trans[i].text) && (t.number == this->trans[i].number) && (t.vct == this->trans[i].vct) )
            remove = i;
    }
    if (remove >= 0)
        this->trans.erase(this->trans.begin() + remove);
}
