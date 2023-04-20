#include "scene.h"
#include "Light.h"
#include "model.h"
#include "inputs.h"
#include <enemy.h>
#include <parallax.h>
#include <player.h>
#include <title.h>
#include <whip.h>
#include <checkCollision.h>

model *startModel = new model();
inputs *KbMs = new inputs();
enemy *walker = new enemy();
parallax *prLX = new parallax();
player *ply = new player();
title *tl = new title();
whip* wep = new whip();
checkCollision *hit = new checkCollision();


float t = 0.2;
clock_t start;

scene::scene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    scne = PLAY;
}

scene::~scene()
{
    //dtor
}

int scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (scne == TITLE) {
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        tl->drawTitle(screenWidth, screenHeight);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3, -0.5, 0);
        tl->drawSquare(screenWidth, screenHeight, 1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3.5, -1.3, 0);
        tl->drawSquare(screenWidth, screenHeight, 2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(4, -2.1, 0);
        tl->drawSquare(screenWidth, screenHeight, 3);
        glPopMatrix();
    }

    else if (scne == PLAY) {
        glPushMatrix(); //matrix for the background parallax
        glScaled(3.33,3.33,1.0);
        prLX->drawSquare(screenWidth,screenHeight);
        glPopMatrix();


        glPushMatrix();
        ply->drawPlayer();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
        glPushMatrix();

        wep->drawWhip(t);
        glPopMatrix();
        glEnable(GL_TEXTURE_2D);

        if (t < 1 && clock() - start > 50) {
            t += 0.1;
            start = clock();
        }
        else if (t >= 1 && clock() - start > 120) {
            wep->wPos.x = 0.0;
            wep->wPos.y = 10.0;
            wep->wPos.z = -2.0;
        }

        walker->drawEnemy();

        /*
        glPushMatrix();
        if(hit->isRadialCollision(player x pos, enemy x pos, player y pos, enemy x pos, player z pos, enemy z pos)){
            do stuff;
        }
        if(hit->isLinearCollision(player x pos, enemy x pos)){
            do stuff;
        }
        glPopMatrix();
        */
    }
}

int scene::initScene()
{
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.0f,0.0f,0.0f,0.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);

    ply->playerInit("images/knight.png", 4, 4);
    walker->enemySkin("images/Walk.png");
    walker->initEnemy(walker->tex, 7, 1);
    walker->placeEnemy(pos3{1.0,0.0,-2.0});

    prLX->initParallax("images/background.png"); //initializing parallax with background image

    tl->initTitle("images/kirb.jpg");
    tl->initOption("images/start.png", 1);
    tl->initOption("images/start.png", 2);
    tl->initOption("images/start.png", 3);

    start = clock();

    return true;
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
            if (scne == PLAY) {
                KbMs->keyPlayer(ply);
            }
            else if (scne == TITLE) {
                int temp = KbMs->keyTitle(tl);
                if (temp == 1) {
                    scne = PLAY;
                }
            }
            break;

        case WM_KEYUP:
            if (scne == PLAY) {
                ply->actions(ply->IDLE);
            }
            break;

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
            if (scne == PLAY) {
                KbMs->mouseWhip(wep, ply, LOWORD(lParam), HIWORD(lParam));
                t = 0.2;
            }
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
