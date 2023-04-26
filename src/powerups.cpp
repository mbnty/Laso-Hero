#include "powerups.h"

powerups::powerups()
{
    //ctor
    powPos.x = 10.0;
    powPos.y = 15.0;
    powPos.z = -2.0;

    scaleSize.x = 1.0;
    scaleSize.y = 1.0;
    scaleSize.z = 1.0;

    isHit = 0;
}

powerups::~powerups()
{
    //dtor
}

void powerups::powTexture(char* fileName)
{
    powLoad->loadTexture(fileName, powTex);
}


void powerups::initPowerUp(GLuint powTex)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    xMax = 1.0;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;

    this->powTex = powTex;
}

void powerups::drawSquare()
{
    powLoad->binder(powTex);

    glTranslatef(powPos.x, -1, powPos.z);
    glScalef(scaleSize.x,scaleSize.y,scaleSize.z);

    glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMin);
        glVertex3f(0.15, 0.15, -1.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(-0.15, 0.15, -1.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(-0.15, -0.15, -1.0);

        glTexCoord2f(xMin, yMax);
        glVertex3f(0.15, -0.15, -1.0);
    glEnd();
}

int powerups::dropPowerUp(pos3 pos)
{
    powPos.x = pos.x;
    powPos.y = pos.y;
    powPos.z = pos.z;
}

void powerups::actions()
{
    if (act == IDLE) {
        powPos.x = 10;
        powPos.y = 15;
    }
}

