#include "fonts.h"

fonts::fonts()
{
    //ctor
    pos.x = 0.5;
    pos.y = 0.5;
    pos.z = 0.0;
    Rotate.x = Rotate.y = Rotate.z = 0;
    zoom = -2.5;
}

fonts::~fonts()
{
    //dtor
}


void fonts::initFonts(char* fileName)
{
    fLoad->loadTexture(fileName, fTex);
}

void fonts::buildFonts(char* str)
{
    for(int i = 0; i < strlen(str); i++){
        switch(str[i])
        {
        case '0':
            C[cCnt].xMin = 0;
            C[cCnt].xMax = 1.0/5,0;
            break;
        }
    }
}

void fonts::drawFonts(int i)
{
    fLoad->binder(fTex);

    glPushMatrix();

    glRotated(Rotate.x, 1, 0, 0);
    glRotated(Rotate.y, 0, 1, 0);
    glRotated(Rotate.z, 0, 0, 1);

    glBegin(GL_QUADS);
        glTexCoord2f(C[i].xMin, 1.0);
        glVertex3f(0, 0, 0);

        glTexCoord2f(C[i].xMax, 1.0);
        glVertex3f(1.0/13.0, 0, 0);

        glTexCoord2f(C[i].xMax, 0.0);
        glVertex3f(1.0/13.0, 1, 0);

        glTexCoord2f(C[i].xMin, 0.0);
        glVertex3f(0, 1, 0);
    glEnd();

    glPopMatrix();
}

