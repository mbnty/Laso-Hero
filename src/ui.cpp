#include "ui.h"

ui::ui()
{
    //ctor
    xMax = 1.0;
    xMin = 0.0;
    yMax = 0.0;
    yMin = 1.0;
    xPos = -13.0;
    yPos = 2.0;
}

ui::~ui()
{
    //dtor
}

void ui::drawSquare(float width, float height, int num)
{
    uLoad->binder(uTex[num]);

    glScalef(0.09, 0.16, 1.0);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMin);
        glVertex3f(-1.0 * width/height, -1.0, -7.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(width/height, -1.0, -7.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(width/height, 1.0, -7.0);

        glTexCoord2f(xMin, yMax);
        glVertex3f(-1.0 * width/height, 1.0, -7.0);
    glEnd();
}

void ui::initUi(char* fileName, int num)
{
    if(num >= 0 && num <= 100){
        uLoad->loadTexture(fileName, uTex[num]);
    }
}
