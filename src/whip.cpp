#include "whip.h"

whip::whip()
{
    //ctor
    wPos.x = 0.0;
    wPos.y = 10.0;
    wPos.z = -2.0;
    run = false;
    t = 0;
}

whip::~whip()
{
    //dtor
}

void whip::initWhip(char* fileName)
{
    tLoad->loadTexture(fileName, tex);
}

void whip::resetWhip()
{
    wPos.x = 0.0;
    wPos.y = 10.0;
    wPos.z = -2.0;
    run = false;
    t = 0;
}

void whip::drawWhip()
{
    tLoad->binder(tex);

    glTranslated(wPos.x, wPos.y, wPos.z);
    glScaled(0.25, 0.25, 1.0);

    GLfloat xpos = wEnd.x * t;

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex3f(0, 1.0, 0);

    glTexCoord2f(1, 1);
    glVertex3f(xpos, 1.0, 0);

    glTexCoord2f(1, 0);
    glVertex3f(xpos, wEnd.y, 0);

    glTexCoord2f(0, 0);
    glVertex3f(0, wEnd.y, 0);

    glEnd();
}
