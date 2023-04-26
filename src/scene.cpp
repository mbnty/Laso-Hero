#include "scene.h"
#include "Light.h"
#include "model.h"
#include "inputs.h"
#include <enemy.h>
#include <parallax.h>
#include <player.h>
#include <title.h>
#include <whip.h>
#include <bullet.h>
#include <checkCollision.h>
#include <platform.h>
#include <lvl1.h>
#include <ui.h>

model *startModel = new model();
inputs *KbMs = new inputs();
enemy *walker = new enemy();
player *ply = new player();
title *tl = new title();
whip* wep = new whip();
checkCollision *hit = new checkCollision();
ui *Hud = new ui();

parallax prLx[4];
bullet ammo[6];

/*
//objects for the platforms for the first level
platform *pl1 = new platform();
platform *pl2 = new platform();
platform *pl3 = new platform();
platform *sp1 = new platform();
*/
lvl1 *l1 = new lvl1();


float t = 0;
int numBullet;
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
        prLx[1].drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        for(int i = 0; i < ply->health; i++){
            glPushMatrix();
            glTranslatef(((Hud->xPos) + i)/3, Hud->yPos, 0);
            Hud->drawSquare(screenWidth, screenHeight, 0);
            glPopMatrix();
        }

        for(int i = 0; i < ply->ammo; i++){
            glPushMatrix();
            glTranslatef(((Hud->xPos) + i)/3, 1.7, 0);
            Hud->drawSquare(screenWidth, screenHeight, 1);
            glPopMatrix();
        }
        /*
        glPushMatrix();
        glTranslatef(3, 2, 0);
        Hud->drawSquare(screenWidth, screenHeight, 0);
        glPopMatrix();
        */

        glPushMatrix(); // this martix holds the platforms
        l1->drawLvl1();
        /*
        pl1->drawPlatform(1,0,3,1);
        //pl2->drawPlatform(5,0,3,1);
        //pl3->drawPlatform(8,0,1,1);
        sp1->drawPlatform(1,-1.4,0.5,0.5);

        glPopMatrix();
        */

        for (int i = 0; i < 6; i++) {
            glPushMatrix();
            ammo[i].drawBullet();
            glPopMatrix();

            if (ammo[i].bPos.x >= 7.0 || ammo[i].bPos.x <= -7.0)
                ammo[i].act = ammo->IDLE;

            if (walker->movement != walker->DIE) {
                if (hit->isRadialCollision(ammo[i].bPos.x, walker->enemyPosition.x, ammo[i].bPos.y, walker->enemyPosition.y, 0.1, 0.5)) {
                    walker->movement = walker->DIE;
                    ammo[i].act = ammo->IDLE;
                }
            }
        }

        glPushMatrix();
        ply->drawPlayer();
        if (ply->actionTrigger == ply->JUMP)
            ply->actions(ply->JUMP);
        else if (ply->actionTrigger == ply->IDLE) {
            ply->actions(ply->IDLE);
        }
        glPopMatrix();

        /*
        if(hit->isLinearCollision(ply->pPos.x, walker->enemyPosition.x)){
            //walker->isHit = true ;
        }
        */

        if(walker->enemyPosition.x > ply->pPos.x && walker->movement != walker->DIE){
            walker->movement = walker->WALKL;
        }
        else if (walker->enemyPosition.x < ply->pPos.x && walker->movement != walker->DIE) {
            walker->movement = walker->WALKR;
        }


        if(walker->isHit == false){
            walker->drawEnemy();
        }

        glPushMatrix();
        wep->drawWhip(t);
        glPopMatrix();

        if (hit->isLinearCollision(wep->wEnd.x * t, walker->enemyPosition.x)) {
            walker->movement = walker->DIE;
        }

        if (wep->run == true) {
            if (t < 1) {
                t += 0.01;
                start = clock();
            }
            else if (t >= 1 && clock() - start > 120) {
                wep->wPos.y = 10.0;
                wep->run = false;
            }
        }
        /*
        if(hit->isLinearCollision(ply->pPos.x, walker->enemyPosition.x)){
            walker->isHit = true ;
        }

        if(walker->isHit == false){ //gets the enemy to rewalk
            if(walker->enDir == 'R'){
                walker->movement = walker->WALKR;
            }
            if(walker->enDir == 'L'){
                walker->movement = walker->WALKL;
            }
            walker->drawEnemy();
        }
        */
    }


    else if(scne == PAUSE){
        glPushMatrix(); //matrix for the background parallax
        glScaled(3.33,3.33,1.0);
        prLx[2].drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0.5, 3);
        prLx[3].drawPopUp(screenWidth, screenHeight, 3);
        glPopMatrix();

        for(int i = 0; i < ply->health; i++){
            glPushMatrix();
            glTranslatef(((Hud->xPos) + i)/3, Hud->yPos, 0);
            Hud->drawSquare(screenWidth, screenHeight, 0);
            glPopMatrix();
        }
        for(int i = 0; i < ply->ammo; i++){
            glPushMatrix();
            glTranslatef(((Hud->xPos) + i)/3, 1.7, 0);
            Hud->drawSquare(screenWidth, screenHeight, 1);
            glPopMatrix();
        }

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
        glPopMatrix();

        glPushMatrix();
        wep->drawWhip(t);
        glPopMatrix();

        walker->movement = walker->IDLE;
        if(walker->isHit == false){
            walker->drawEnemy();
        }

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

    prLx[1].initParallax("images/background1.jpg"); //initializing parallax with background image
    prLx[2].initParallax("images/menu.png");
    prLx[3].initPopUp("images/tempPause.png", 3);

    tl->initTitle("images/title.png", 0);
    tl->initTitle("images/menu.png", 1);
    tl->initTitle("images/start.png", 2);
    tl->initTitle("images/help.png", 3);
    tl->initTitle("images/credit.png", 4);
    tl->initTitle("images/stop.png", 5);

    ammo[0].projTexture("images/bullet.png");
    for (int i = 1; i < 6; i++) {
        ammo[i].initBullet(ammo[0].tex);
    }

    /*
    //initialization of the images for the platforms
    pl1->initPlatform("images/platform1.png",1,1);
    pl2->initPlatform("images/platform1.png",1,1);
    pl3->initPlatform("images/platform1.png",1,1);
    sp1->initPlatform("images/spikes.png",1,1);
    */
    l1->initLvl1();

    Hud->initUi("images/heart.png", 0);
    Hud->initUi("images/ammo.png", 1);
    //F->buildFonts((char*)ply->health);

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
                KbMs->keyEnv(prLx[1], 0.005);
                KbMs->keyEnvL1(l1,0.05);
                KbMs->keyEnemy(walker);
                //KbMs->keyBullet(ammo, ply);
                wep->wPos.y = 10.0;
                if((KbMs->keyPause(prLx[1])) == true){ //if H key is pressed
                    scne = PAUSE; //pause the game
                }
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
                    PostQuitMessage(0);
                }
            }
            else if(scne = PAUSE){
                if((KbMs->keyPause(prLx[2])) == 1){ //check if ESC key is pressed
                    scne = PLAY; //resume game
                }
            else if((KbMs->keyPause(prLx[2])) == 2){
                scne = MENU; //return to title screen
            }
        }
            break;

        case WM_KEYUP:
            if (scne == PLAY) {
                ply->actions(ply->IDLE);
            }
            break;

        case WM_LBUTTONDOWN:
            if (scne == PLAY) {
                KbMs->mouseWhip(wep, ply, LOWORD(lParam), HIWORD(lParam));
                t = 0;
            }
            else if (scne == TITLE) {
                scne = MENU;
            }
            break;

        case WM_RBUTTONDOWN:
            numBullet = ply->ammo - 1;
            if (numBullet >= 0) {
                ammo[numBullet].placeBullet(ply->pPos);
                if (ply->playerDir == 'L')
                    ammo[numBullet].act = ammo->MOVEL;
                else if (ply->playerDir == 'R')
                    ammo[numBullet].act = ammo->MOVER;
                ply->ammo--;
            }
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
