#include "bullet.h"

bullet::bullet()
{
    //ctor
    bPos.x = 0.0;
    bPos.y = 15.0;
    bPos.z = -2.0;

    act = IDLE;
    start = clock();
}

bullet::~bullet()
{
    //dtor
}

void bullet::drawBullet()
{
    tLoad->binder(tex);

    glTranslatef(bPos.x, bPos.y, bPos.z);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMin);
        glVertex3f(0.15, 0.15, -2.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(-0.15, 0.15, -2.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(-0.15, -0.15, -2.0);

        glTexCoord2f(xMin, yMax);
        glVertex3f(0.15, -0.15, -2.0);
    glEnd();
    actions();
}

void bullet::placeBullet(vec3 pos)
{
    bPos.x = pos.x;
    bPos.y = pos.y;
    bPos.z = pos.z + 0.1;
}

void bullet::initBullet(GLuint tex)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    xMax = 1.0;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;

    this->tex = tex;
}

void bullet::projTexture(char* fileName)
{
    tLoad->loadTexture(fileName, tex);
}

void bullet::actions()
{
    if (act == IDLE) {
        bPos.x = 0;
        bPos.y = 15;
    }

    if (act == MOVEL) {
        xMax = 0.0;
        xMin = 1.0;
        if (clock() - start > 60) {
            bPos.x -= 0.3;
            start = clock();
        }
    }

    if (act == MOVER) {
        xMax = 1.0;
        xMin = 0.0;
        if (clock() - start > 60) {
            bPos.x += 0.3;
            start = clock();
        }
    }
}
