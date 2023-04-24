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
#include <platform.h>
#include <lvl1.h>

model *startModel = new model();
inputs *KbMs = new inputs();
enemy *walker = new enemy();
parallax *prLX = new parallax();
player *ply = new player();
title *tl = new title();
whip* wep = new whip();
checkCollision *hit = new checkCollision();

/*
//objects for the platforms for the first level
platform *pl1 = new platform();
platform *pl2 = new platform();
platform *pl3 = new platform();
platform *sp1 = new platform();
*/
lvl1 *l1 = new lvl1();


float t = 0.2;
clock_t start;

scene::scene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    scne = TITLE;
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
    }

    else if (scne == MENU) {
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        tl->drawMenu(screenWidth, screenHeight);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0, 0);
        tl->drawSquare(screenWidth, screenHeight, 2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -1, 0);
        tl->drawSquare(screenWidth, screenHeight, 3);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -2, 0);
        tl->drawSquare(screenWidth, screenHeight, 4);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -3, 0);
        tl->drawSquare(screenWidth, screenHeight, 5);
        glPopMatrix();
    }

    else if (scne == PLAY) {
        glPushMatrix(); //matrix for the background parallax
        glScaled(3.33,3.33,1.0);
        prLX->drawSquare(screenWidth,screenHeight);
        glPopMatrix();


        glPushMatrix(); // this martix holds the platforms
        l1->drawLvl1();
        /*
        pl1->drawPlatform(1,0,3,1);
        //pl2->drawPlatform(5,0,3,1);
        //pl3->drawPlatform(8,0,1,1);
        sp1->drawPlatform(1,-1.4,0.5,0.5);
        */
        glPopMatrix();


        glPushMatrix();
        ply->drawPlayer();
        if (ply->actionTrigger == ply->JUMP)
            ply->actions(ply->JUMP);
        else if (ply->actionTrigger == ply->IDLE) {
            ply->actions(ply->IDLE);
        }
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
            wep->wPos.y = 10.0;
        }

        if(hit->isLinearCollision(ply->pPos.x, walker->enemyPosition.x)){
            walker->isHit = true ;
        }

        if(walker->isHit == false){
            walker->drawEnemy();
        }



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
    walker->placeEnemy(pos3{1.0,-0.25,-2.0});

    prLX->initParallax("images/background1.jpg"); //initializing parallax with background image

    tl->initTitle("images/title.png", 0);
    tl->initTitle("images/menu.png", 1);
    tl->initTitle("images/start.png", 2);
    tl->initTitle("images/help.png", 3);
    tl->initTitle("images/credit.png", 4);
    tl->initTitle("images/stop.png", 5);

    /*
    //initialization of the images for the platforms
    pl1->initPlatform("images/platform1.png",1,1);
    pl2->initPlatform("images/platform1.png",1,1);
    pl3->initPlatform("images/platform1.png",1,1);
    sp1->initPlatform("images/spikes.png",1,1);
    */
    l1->initLvl1();

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
            if (scne == PLAY && ply->actionTrigger != ply->JUMP) {
                KbMs->keyPlayer(ply);
                KbMs->keyEnv(prLX, 0.005);
                KbMs->keyEnvL1(l1,0.05);
                wep->wPos.y = 10.0;
            }
            else if (scne == TITLE) {
                scne = MENU;
            }
            else if (scne == MENU) {
                int temp = KbMs->keyTitle(tl);
                if (temp == 2) {
                    scne = PLAY;
                }
                else if (temp == 3) {
                    //scne = HELP;
                }
                else if (temp == 4) {
                    //scne = CREDITS;
                }
                else if (temp == 5) {
                    // How to close program?
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
            else if (scne == TITLE) {
                scne = MENU;
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
