#include "scene.h"
#include "Light.h"
#include "model.h"
#include "inputs.h"
#include <enemy.h>
#include <parallax.h>
#include <player.h>

model *startModel = new model();
inputs *KbMs = new inputs();
enemy *walker = new enemy();
parallax *prLX = new parallax();
player *ply = new player();

scene::scene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
}

scene::~scene()
{
    //dtor
}

int scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    /*
    glColor3f(0.0f, 1.0f, 1.0f);
    glTranslatef(0,0,-8.0f);
    glPushMatrix();
    startModel->drawModel();
    glPopMatrix();*/

    glPushMatrix();
    ply->drawPlayer();
    glPopMatrix();

    glPushMatrix(); //matrix for the background parallax
    glScaled(3.33,3.33,1.0);
    prLX->drawSquare(screenWidth,screenHeight);
    glPopMatrix();

    walker->drawEnemy(); //currently crashes unsure why
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

    glEnable(GL_TEXTURE_2D);

    ply->playerInit("images/eg-1.png", 6, 4);
    walker->enemySkin("images/mon.png");
    walker->initEnemy(walker->tex, 7, 1);
    walker->placeEnemy(pos3{0.0,0.0,-8.0});

    prLX->initParallax("images/background.png"); //initializing parallax with background image
}

void scene::resizeSceneWin(GLsizei width, GLsizei height)
{
    screenWidth= width;
    screenHeight = height;
    float ratio = (float)width/(float)height;
    glViewport(0,0, width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,ratio,0.1,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    KbMs->updateWParam(wParam);

    switch(uMsg) {
        case WM_KEYDOWN:
            KbMs->keyPlayer(ply);
            break;

        case WM_KEYUP:
            ply->actions(ply->IDLE);
            break;

        case WM_LBUTTONDOWN:
            break;

        case WM_RBUTTONDOWN:
            break;

        case WM_MBUTTONDOWN:
            break;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            break;

        case WM_MOUSEMOVE:
            break;

        case WM_MOUSEWHEEL:
            break;
    }
}
