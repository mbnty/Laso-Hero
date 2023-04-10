#include "title.h"

title::title()
{
    xMax = 1.0;
    xMin = 0.0;
    yMax = 0.0;
    yMin = 1.0;
    selection = 1;
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

void title::initTitle(char* fileName)
{
    bTex->loadTexture(fileName, tex[0]);
}

void title::initOption(char* fileName, int num)
{
    if (num >= 1 && num <= 3) {
        bTex->loadTexture(fileName, tex[num]);
    }
}
