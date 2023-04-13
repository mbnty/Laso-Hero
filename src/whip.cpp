#include "whip.h"

whip::whip()
{
    //ctor
    wPos.x = 0.0;
    wPos.y = 10.0;
    wPos.z = -2.0;
}

whip::~whip()
{
    //dtor
}

void whip::drawWhip(float t)
{
    glTranslated(wPos.x, wPos.y, wPos.z);
    glColor3f(0.0, 0.0, 0.0);
    glScaled(0.25, 0.25, 1.0);
    glLineWidth(5.0);

    GLfloat xpos = x * t;
    GLfloat ypos = y * t;

    glBegin(GL_LINES);
    glVertex3f(0, 1.0, 0);
    glVertex3f(xpos, ypos, 0);
    glEnd();
}
