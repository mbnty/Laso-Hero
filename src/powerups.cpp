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
    act = INIT;
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

void powerups::resetPowerUp()
{
    powPos.x = 10.0;
    powPos.y = 15.0;
    powPos.z = -2.0;

    isHit = 0;
    act = INIT;
}

void powerups::drawSquare()
{
    powLoad->binder(powTex);

    glTranslatef(powPos.x, powPos.y, powPos.z);
    glScalef(scaleSize.x,scaleSize.y,scaleSize.z);

    glBegin(GL_QUADS);
        glTexCoord2f(xMin, yMin);
        glVertex3f(0.1, 0.1, 0.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(-0.1, 0.1, 0.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(-0.1, -0.1, 0.0);

        glTexCoord2f(xMin, yMax);
        glVertex3f(0.1, -0.1, 0.0);
    glEnd();
}

void powerups::dropBullet(pos3 pos)
{
    int chance = (int)(rand()%100);
    if(chance < 31){ //if certain chance reached, drop the bullet
        isDropped = true;
        powPos.x = pos.x;
        powPos.y = pos.y - 0.4;
        powPos.z = -2.0;
    }
}

void powerups::dropHealth(pos3 pos)
{
    int chance = (int)(rand()%100);
    if(chance < 21){ //if certain chance reached, drop the health
        isDropped = true;
        powPos.x = pos.x;
        powPos.y = pos.y - 0.4;
        powPos.z = -2.0;
    }
}


void powerups::actions()
{
    switch(act){
    case IDLE:
        powPos.x += 0;
        powPos.y += 0;
        powPos.z += 0;
        break;

    case INIT:
        powPos.x = 10.0;
        powPos.y = 15.0;
        powPos.z = -2.0;
        break;

    case PICKUP:
        powPos.x = 10.0;
        powPos.y = 15.0;
        isHit = 0;
        break;
    }
}
