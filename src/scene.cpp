#include "scene.h"
#include "Light.h"
#include "model.h"

model *startModel = new model();

scene::scene()
{
    //ctor
}

scene::~scene()
{
    //dtor
}

int scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.0f, 1.0f, 1.0f);

    glTranslatef(0,0,-8.0f);
    glPushMatrix();
    startModel->drawModel();
    glPopMatrix();
}

int scene::initScene()
{
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0,0,0,0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    Light Lite(GL_LIGHT0);
    Lite.setLight(GL_LIGHT0);
}

void scene::resizeSceneWin(GLsizei width, GLsizei height)
{
    float ratio = (float)width/(float)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0,ratio,0.1,1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
