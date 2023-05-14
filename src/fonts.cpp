#include "fonts.h"

fonts::fonts()
{
    //ctor
    pos.x = 1.25;
    pos.y = 0.6;
    pos.z = 0.0;
    Rotate.x = Rotate.y = Rotate.z = 0;
    zoom = -2.5;
    run = false;
}

fonts::~fonts()
{
    //dtor

}

void fonts::initFonts(char *Filename)
{
    tLoad->loadTexture(Filename, tex);
}

void fonts::buildFonts(int str)
{
    if (cCnt > 1) { cCnt = 1; }
    switch(str) {
        case 0:
            xMin = 0;
            xMax = 1.0/5.0;
            yMin = 0.0;
            yMax = 1.0/2.0;
            break;
        case 1:
            xMin = 1.0/5.0;
            xMax = 2.0/5.0;
            yMin = 0.0;
            yMax = 1.0/2.0;
            break;
        case 2:
            xMin = 2.0/5.0;
            xMax = 3.0/5.0;
            yMin = 0.0;
            yMax = 1.0/2.0;
            break;
        case 3:
            xMin = 3.0/5.0;
            xMax = 4.0/5.0;
            yMin = 0.0;
            yMax = 1.0/2.0;
            break;
        case 4:
            xMin = 4.0/5.0;
            xMax = 5.0/5.0;
            yMin = 0.0;
            yMax = 1.0/2.0;
            break;
        case 5:
            xMin = 0.0;
            xMax = 1.0/5.0;
            yMin = 1.0/2.0;
            yMax = 1.0;
            pos.y += 0.02;
            break;
        case 6:
            xMin = 1.0/5.0;
            xMax = 2.0/5.0;
            yMin = 1.0/2.0;
            yMax = 1.0;
            pos.y += 0.02;
            break;
        case 7:
            xMin = 2.0/5.0;
            xMax = 3.0/5.0;
            yMin = 1.0/2.0;
            yMax = 1.0;
            pos.y += 0.02;
            break;
        case 8:
            xMin = 3.0/5.0;
            xMax = 4.0/5.0;
            yMin = 1.0/2.0;
            yMax = 1.0;
            pos.y += 0.02;
            break;
        case 9:
            xMin = 4.0/5.0;
            xMax = 5.0/5.0;
            yMin = 1.0/2.0;
            yMax = 1.0;
            pos.y += 0.02;
            break;
    }
    cCnt++;
}

void fonts::drawFonts(int i, float shift)
{
    tLoad->binder(tex);

    glPushMatrix();

    glRotated(Rotate.x, 1, 0, 0);
    glRotated(Rotate.y, 0, 1, 0);
    glRotated(Rotate.z, 0, 0, 1);
    glTranslatef(pos.x + shift, pos.y, zoom);
    glScalef(0.3, 0.15, 0.0);

    glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMax);
        glVertex3f(0.0, 0.0, zoom);

        glTexCoord2f(xMax, yMax);
        glVertex3f(1.0/5.0, 0.0, zoom);

        glTexCoord2f(xMax, yMin);
        glVertex3f(1.0/5.0, 1.0, zoom);

        glTexCoord2f(xMin, yMin);
        glVertex3f(0.0, 1.0, zoom);
    glEnd();

    glPopMatrix();
}
