#include "model.h"

model::model()
{
    //ctor
    rotateModelX = 0;
    posModelX = 0;
    posModelY = 0;
}

model::~model()
{
    //dtor
}

void model::drawModel()
{
    //glTranslated(posModelX, posModelY, -8.0f);

    glRotatef(rotateModelX, 1, 0, 0);

    glutSolidCube(1.3f);
}
