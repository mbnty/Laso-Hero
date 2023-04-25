#include "enemy.h"

enemy::enemy()
{
    enemyPosition.x = 0.0;
    enemyPosition.y = -0.65;
    enemyPosition.z = -2.5;

    enemySize.x = 1.0;
    enemySize.y = 0.5;

    enemyRotation.x = enemyRotation.y = enemyRotation.z = 0;
    movement = WALKL;

    enemySpeed.x = 0.01;
    enemySpeed.y = 0.0;

    isHit = false;

    currTime = clock();

    indexTexture = 0;
}

enemy::~enemy()
{
    //dtor
}

void enemy::drawEnemy()
{
    tLoad->binder(tex);

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslated(enemyPosition.x, enemyPosition.y, enemyPosition.z);
    glRotatef(enemyRotation.x,1,0,0);
    glRotatef(enemyRotation.y,0,1,0);
    glRotatef(enemyRotation.z,0,0,1);

    glScalef(enemySize.x,enemySize.y, 1);

    glBegin(GL_POLYGON);

    glTexCoord2f(xMin, yMin);
    glVertex3f(1.0,1.0,0.0);

    glTexCoord2f(xMax, yMin);
    glVertex3f(-1.0,1.0,0.0);

    glTexCoord2f(xMax, yMax);
    glVertex3f(-1.0,-1.0,0.0);

    glTexCoord2f(xMin, yMax);
    glVertex3f(1.0,-1.0,0.0);

    glEnd();


    actions();
    glPopMatrix();
}

void enemy::placeEnemy(pos3 placement)
{
    enemyPosition.x = placement.x;
    enemyPosition.y = placement.y;
    enemyPosition.z = placement.z;
}

void enemy::initEnemy(GLuint textSkin, int verticalFrames, int horizontalFrames)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    vFrames = verticalFrames;
    hFrames = horizontalFrames;

    xMax = 1.0/(float)verticalFrames;
    xMin = 0.0;
    yMax = 1.0/(float)horizontalFrames;
    yMin = 0.0;

    this->tex = tex;
}

void enemy::enemySkin(char* fileName)
{
    tLoad->loadTexture(fileName,tex);
}

void enemy::actions()
{
    switch(movement){
    case IDLE: //stops the enemy from moving
        enemyPosition.x += 0;
        enemyPosition.y += 0;
        enemyPosition.z += 0;
        break;
    case WALKR:
        if(clock() - currTime > 60){
            xMax += 1.0/(float)vFrames;
            xMin += 1.0/(float)vFrames;
            enemyPosition.x += enemySpeed.x;
            currTime = clock();
        }
        break;
    case WALKL:
        if(clock() - currTime > 60){
            xMax += 1.0/(float)vFrames;
            xMin += 1.0/(float)vFrames;
            enemyPosition.x -= enemySpeed.x;
            currTime = clock();
        }
        break;
    }
}
