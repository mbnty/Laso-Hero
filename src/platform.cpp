#include "platform.h"

platform::platform()
{
    //ctor
    verts[0].x = -0.25; verts[0].y = -0.25; verts[0].z = -1.0;
    verts[1].x = 0.25; verts[1].y = -0.25; verts[1].z = -1.0;
    verts[2].x = 0.25; verts[2].y = 0.25; verts[2].z = -1.0;
    verts[3].x = -0.25; verts[3].y = 0.25; verts[3].z = -1.0;

    pos.x = 0;
    pos.y = 0.0;
    pos.z = -2;

    scaleSize.x = 1.0;
    scaleSize.y = 1.0;
    scaleSize.z = 1.0;

    alpha = 1.0;
}

platform::~platform()
{
    //dtor
}

void platform::drawPlatform()
{
    tLoad->binder(tex);
    glPushMatrix();
    glTranslated(pos.x, pos.y, pos.z);
    glScalef(scaleSize.x,scaleSize.y,scaleSize.z);
    glColor4f(1.0, 1.0, 1.0, alpha);

    glBegin(GL_QUADS);

    glTexCoord2f(xMin, yMax);
    glVertex3f(verts[0].x, verts[0].y, verts[0].z);

    glTexCoord2f(xMax, yMax);
    glVertex3f(verts[1].x, verts[1].y, verts[1].z);

    glTexCoord2f(xMax, yMin);
    glVertex3f(verts[2].x, verts[2].y, verts[2].z);

    glTexCoord2f(xMin, yMin);
    glVertex3f(verts[3].x, verts[3].y, verts[3].z);

    glEnd();
    glPopMatrix();
}

void platform::initPlatform(char* fileName, int vFrm, int hFrm)
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    vFrames = vFrm;
    hFrames = hFrm;

    xMax = 1.0/(float)vFrm;
    xMin = 0.0;
    yMax = 1.0/(float)hFrm;
    yMin = 0.0;

    tLoad->loadTexture(fileName, tex);
}

void platform::place(float posX, float posY, float scaleX, float scaleY)
{
    pos.x = posX;
    pos.y = posY;
    scaleSize.x = scaleX;
    scaleSize.y = scaleY;
}
