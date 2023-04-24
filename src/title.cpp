#include "title.h"

title::title()
{
    xMax = 1.0;
    xMin = 0.0;
    yMax = 0.0;
    yMin = 1.0;
    selection = 2;
}

title::~title()
{
    //dtor
}

void title::drawTitle(float width, float height)
{
    glColor3f(1.0, 1.0, 1.0);
    bTex->binder(tex[0]);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMin);
        glVertex3f(-1.0 * width/height, -1.0, -10.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(width/height, -1.0, -10.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(width/height, 1.0, -10.0);

        glTexCoord2f(xMin, yMax);
        glVertex3f(-1.0 * width/height, 1.0, -10.0);
    glEnd();
}

void title::drawMenu(float width, float height)
{
    glColor3f(1.0, 1.0, 1.0);
    bTex->binder(tex[1]);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMin);
        glVertex3f(-1.0 * width/height, -1.0, -10.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(width/height, -1.0, -10.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(width/height, 1.0, -10.0);

        glTexCoord2f(xMin, yMax);
        glVertex3f(-1.0 * width/height, 1.0, -10.0);
    glEnd();
}


void title::drawSquare(float width, float height, int num)
{
    if (selection == num) {
        glColor3f(0.56, 0.93, 0.56);
    }
    else {
        glColor3f(1.0, 1.0, 1.0);
    }

    bTex->binder(tex[num]);

    glScalef(1, 0.4, 1.0);
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMin);
        glVertex3f(-1.0 * width/height, -1.0, -9.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(width/height, -1.0, -9.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(width/height, 1.0, -9.0);

        glTexCoord2f(xMin, yMax);
        glVertex3f(-1.0 * width/height, 1.0, -9.0);
    glEnd();
}

void title::initTitle(char* fileName, int num)
{
    bTex->loadTexture(fileName, tex[num]);
}
