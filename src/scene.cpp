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
#include <powerups.h>

model *startModel = new model();
inputs *KbMs = new inputs();
enemy *walker = new enemy();
player *ply = new player();
title *tl = new title();
whip* wep = new whip();
checkCollision *hit = new checkCollision();
ui *Hud = new ui();
powerups *spec = new powerups();

parallax prLx[5];
bullet ammo[6];

//objects for the platforms for the first level
platform *pl1 = new platform();
platform *pl2 = new platform();
platform *pl3 = new platform();
platform *pl4 = new platform();
platform *pl5 = new platform();

platform *sp1 = new platform();
platform *sp2 = new platform();
platform *sp3 = new platform();

//objects for the platforms for the second level
platform *pl21 = new platform();
platform *pl22 = new platform();
platform *pl23 = new platform();
platform *pl24 = new platform();
platform *pl25 = new platform();




int numBullet;
int level = 0;
clock_t start;
clock_t run;

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

    else if (scne == LV1) {
        if (ply->health < 0)
            PostQuitMessage(0);

        glPushMatrix(); //matrix for the background parallax
        glScaled(3.33,3.33,1.0);
        prLx[level].drawSquare(screenWidth,screenHeight);
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
        pl1->drawPlatform();
        sp1->drawPlatform();
        pl2->drawPlatform();
        pl3->drawPlatform();
        sp2->drawPlatform();
        pl4->drawPlatform();
        pl5->drawPlatform();
        sp2->drawPlatform();
        glPopMatrix();

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

        if(walker->movement == walker->DIE){
            spec->dropPowerUp(walker->enemyPosition);
            spec->powPos.z = -2.0;
        }

        if(hit->isLinearCollision(spec->powPos.x, ply->pPos.x)){
            spec->isHit++;
        }
        if(spec->isHit == 1){
            spec->act = spec->IDLE;
            ply->ammo++;
        }
        glPushMatrix();
        spec->drawSquare();
        glPopMatrix();

        if (ply->pColor.y < 1) {
            ply->pColor.y += 0.003;
            ply->pColor.z += 0.003;
        }

        glPushMatrix();
        ply->drawPlayer();
        if (ply->actionTrigger == ply->JUMP)
            ply->actions(ply->JUMP);
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

        if (!walker->isDead && hit->isQuadCollisionEnemy(ply, walker) && clock() - ply->damage > 2000) {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
        }

        if(walker->isHit == false){
            walker->drawEnemy();
        }


        //check if collision with top of platform 1
        if ((ply->pPos.y ) >= (pl1->pos.y +(0.25 * pl1->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl1))
        {
            ply->actions(ply->IDLE);
            ply->groundValue = (pl1->pos.y +(0.25 * pl1->scaleSize.y)) + 0.4;
        }

        else if ((ply->pPos.y ) >= (pl1->pos.y +(0.25 * pl1->scaleSize.y)) && !hit->isQuadCollisionPlatform(ply,pl1))
        {   //scuffed version of getting on the platform
            ply->t = 8.2;
            ply->actions(ply->JUMP);
            ply->groundValue = -0.65;
            if(ply->pPos.y == -0.65)
            {
                ply->actionTrigger = ply->IDLE;
                ply->t = 1 ;
            }
        }
        //check if collision with top of platform 2
        if ((ply->pPos.y ) >= (pl2->pos.y +(0.25 * pl2->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl2))
        {
            ply->groundValue = (pl2->pos.y +(0.25 * pl2->scaleSize.y)) + 0.4;
            if(ply->pPos.y == (pl2->pos.y +(0.25 * pl2->scaleSize.y)) + 0.4)
            {
                //ply->actionTrigger = ply->IDLE;
                ply->t = 1;
            }
        }
        //check if collision with top of platform 3
        if ((ply->pPos.y ) >= (pl3->pos.y +(0.25 * pl3->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl3))
        {
            ply->groundValue = (pl3->pos.y +(0.25 * pl3->scaleSize.y)) + 0.4;
            ply->actions(ply->IDLE);
        }
        //check if collision with top of platform 4
        if ((ply->pPos.y ) >= (pl4->pos.y +(0.25 * pl4->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl4))
        {
            ply->groundValue = (pl4->pos.y +(0.25 * pl4->scaleSize.y)) + 0.4;
            ply->actions(ply->IDLE);
        }
        //check if collision with top of platform 5
        if ((ply->pPos.y ) >= (pl5->pos.y +(0.25 * pl5->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl5))
        {
            ply->groundValue = (pl5->pos.y +(0.25 * pl5->scaleSize.y)) + 0.4;
            ply->actions(ply->IDLE);
        }


        //check if collision with spikes
        if (hit->isQuadCollisionPlatform(ply,sp1) && clock() - ply->damage > 2000)
        {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
        }

        if (hit->isQuadCollisionPlatform(ply,sp2) && clock() - ply->damage > 2000)
        {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
        }

        if (hit->isQuadCollisionPlatform(ply,sp3) && clock() - ply->damage > 2000)
        {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
        }


        glPushMatrix();
        wep->drawWhip();
        glPopMatrix();

        if (wep->run == true) {
            if (hit->isQuadCollisionWhip(wep, walker)) {
                walker->movement = walker->DIE;
            }

            if (wep->t < 1) {
                wep->t += 0.01;
                start = clock();
            }
            else if (wep->t >= 1 && clock() - start > 120) {
                wep->wPos.y = 10.0;
                wep->run = false;
            }
        }

        if (clock() - run > 30) {
            KbMs->keyPlayer(ply);
            KbMs->keyEnv(prLx[1], 0.005);
            KbMs->keyEnemy(walker);

            KbMs->keyEnvL1(pl1,0.05);
            KbMs->keyEnvL1(pl2,0.05);
            KbMs->keyEnvL1(pl3,0.05);
            KbMs->keyEnvL1(pl4,0.05);
            KbMs->keyEnvL1(pl5,0.05);

            KbMs->keyEnvL1(sp1,0.05);
            KbMs->keyEnvL1(sp2,0.05);
            KbMs->keyEnvL1(sp3,0.05);

            KbMs->keyPowerUp(spec, 0.05);
            run = clock();
        }
    }

    else if (scne == LV2) {
        glPushMatrix(); //matrix for the background parallax
        glScaled(3.33,3.33,1.0);
        prLx[level].drawSquare(screenWidth,screenHeight);
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
        pl21->drawPlatform();
        pl22->drawPlatform();
        pl23->drawPlatform();
        pl24->drawPlatform();
        pl25->drawPlatform();
        glPopMatrix();

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

        if(walker->movement == walker->DIE){
            spec->dropPowerUp(walker->enemyPosition);
            spec->powPos.z = -2.0;
        }

        if(hit->isLinearCollision(spec->powPos.x, ply->pPos.x)){
            spec->isHit++;
        }
        if(spec->isHit == 1){
            spec->act = spec->IDLE;
            ply->ammo++;
        }
        glPushMatrix();
        spec->drawSquare();
        glPopMatrix();

        if (ply->pColor.y < 1) {
            ply->pColor.y += 0.003;
            ply->pColor.z += 0.003;
        }

        glPushMatrix();
        ply->drawPlayer();
        if (ply->actionTrigger == ply->JUMP)
            ply->actions(ply->JUMP);
        else if (ply->actionTrigger == ply->IDLE) {
            ply->actions(ply->IDLE);
        }
        glPopMatrix();

        if (!walker->isDead && hit->isQuadCollisionEnemy(ply, walker) && clock() - ply->damage > 2000) {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
        }

        //check if collision with top of platform 1
        if ((ply->pPos.y ) >= (pl21->pos.y +(0.25 * pl21->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl21))
        {
            ply->groundValue = (pl21->pos.y +(0.25 * pl21->scaleSize.y)) + 0.4;
            cout << ply->actionTrigger << endl;
        }

        else if ((ply->pPos.y ) >= (pl21->pos.y +(0.25 * pl21->scaleSize.y)) && !hit->isQuadCollisionPlatform(ply,pl21))
        {   //scuffed version of getting on the platform
            ply->t = 8.2;
            ply->actions(ply->JUMP);
            ply->groundValue = -0.65;
            if(ply->pPos.y == -0.65)
            {
                ply->actionTrigger = ply->IDLE;
                ply->t = 1 ;
            }
        }
        //check if collision with top of platform 2
        if ((ply->pPos.y ) >= (pl22->pos.y +(0.25 * pl22->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl22))
        {
            ply->groundValue = (pl22->pos.y +(0.25 * pl22->scaleSize.y)) + 0.4;
            if(ply->pPos.y == (pl22->pos.y +(0.25 * pl1->scaleSize.y)) + 0.4)
            {
                ply->actionTrigger = ply->IDLE;
                ply->t = 1;
            }
        }
        //check if collision with top of platform 3
        if ((ply->pPos.y ) >= (pl23->pos.y +(0.25 * pl23->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl23))
        {
            ply->groundValue = (pl23->pos.y +(0.25 * pl23->scaleSize.y)) + 0.4;
            ply->actions(ply->IDLE);
            cout << ply->t << endl;
        }
        //check if collision with top of platform 4
        if ((ply->pPos.y ) >= (pl24->pos.y +(0.25 * pl24->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl24))
        {
            ply->groundValue = (pl24->pos.y +(0.25 * pl24->scaleSize.y)) + 0.4;
            ply->actions(ply->IDLE);
            cout << ply->t << endl;
        }
        //check if collision with top of platform 5
        if ((ply->pPos.y ) >= (pl25->pos.y +(0.25 * pl25->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl25))
        {
            ply->groundValue = (pl25->pos.y +(0.25 * pl25->scaleSize.y)) + 0.4;
            ply->actions(ply->IDLE);
            cout << ply->t << endl;
        }

        glPushMatrix();
        wep->drawWhip();
        glPopMatrix();

        if (wep->run == true) {
            if (hit->isQuadCollisionWhip(wep, walker)) {
                walker->movement = walker->DIE;
            }

            if (wep->t < 1) {
                wep->t += 0.01;
                start = clock();
            }
            else if (wep->t >= 1 && clock() - start > 120) {
                wep->wPos.y = 10.0;
                wep->run = false;
            }
        }
    }

    else if (scne == LV3) {
        glPushMatrix(); //matrix for the background parallax
        glScaled(3.33,3.33,1.0);
        prLx[level].drawSquare(screenWidth,screenHeight);
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

        if(walker->movement == walker->DIE){
            spec->dropPowerUp(walker->enemyPosition);
            spec->powPos.z = -2.0;
        }

        if(hit->isLinearCollision(spec->powPos.x, ply->pPos.x)){
            spec->isHit++;
        }
        if(spec->isHit == 1){
            spec->act = spec->IDLE;
            ply->ammo++;
        }
        glPushMatrix();
        spec->drawSquare();
        glPopMatrix();

        if (ply->pColor.y < 1) {
            ply->pColor.y += 0.003;
            ply->pColor.z += 0.003;
        }

        glPushMatrix();
        ply->drawPlayer();
        if (ply->actionTrigger == ply->JUMP)
            ply->actions(ply->JUMP);
        glPopMatrix();

        if (!walker->isDead && hit->isQuadCollisionEnemy(ply, walker) && clock() - ply->damage > 2000) {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
        }

        glPushMatrix();
        wep->drawWhip();
        glPopMatrix();

        if (wep->run == true) {
            if (hit->isQuadCollisionWhip(wep, walker)) {
                walker->movement = walker->DIE;
            }

            if (wep->t < 1) {
                wep->t += 0.01;
                start = clock();
            }
            else if (wep->t >= 1 && clock() - start > 120) {
                wep->wPos.y = 10.0;
                wep->run = false;
            }
        }
    }


    else if(scne == PAUSE){
        glPushMatrix(); //matrix for the background parallax
        glScaled(3.33,3.33,1.0);
        prLx[level].drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 1);
        glTranslatef(0, 0, -2);
        prLx[4].drawPopUp(screenWidth, screenHeight, 3);
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

        if (level = 1) {
            glPushMatrix(); // this martix holds the platforms
            pl1->drawPlatform();
            sp1->drawPlatform();
            pl2->drawPlatform();
            pl3->drawPlatform();
            sp2->drawPlatform();
            pl4->drawPlatform();
            pl5->drawPlatform();
            sp2->drawPlatform();
            glPopMatrix();

            //walker->movement = walker->IDLE;
            if(!walker->isDead){
                walker->movement = walker->IDLE;
            }
            if(walker->isHit == false){
                walker->drawEnemy();
            }
        }

        glPushMatrix();
        ply->drawPlayer();
        glPopMatrix();

        glPushMatrix();
        wep->drawWhip();
        glPopMatrix();
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
    prLx[2].initParallax("images/background2.jpg");
    prLx[3].initParallax("images/background3.png");
    prLx[4].initPopUp("images/tempPause.png", 3);

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

    spec->powTexture("images/ammo.png");
    spec->initPowerUp(spec->powTex);

    //initialization of the images for the platforms
    //level 1
    pl1->initPlatform("images/platform1.png",1,1);
    pl2->initPlatform("images/platform1.png",1,1);
    pl3->initPlatform("images/platform1.png",1,1);
    pl4->initPlatform("images/platform1.png",1,1);
    pl5->initPlatform("images/platform1.png",1,1);

    sp1->initPlatform("images/spikes.png",1,1);
    sp2->initPlatform("images/spikes.png",1,1);
    sp3->initPlatform("images/spikes.png",1,1);

    pl1->place(0,0,5,1);
    sp1->place(1,-1.0,1,0.5);
    pl2->place(6,0,3,1);
    pl3->place(10,0,2,1);
    sp2->place(11,-1.0,1,0.5);
    pl4->place(11.5,0,2,1);
    pl5->place(18,0,5,1);
    sp3->place(18,-1.0,2,0.5);

    //level 2
    pl21->initPlatform("images/platform2.png",1,1);
    pl22->initPlatform("images/platform2.png",1,1);
    pl23->initPlatform("images/platform2.png",1,1);
    pl24->initPlatform("images/platform2.png",1,1);
    pl25->initPlatform("images/platform2.png",1,1);

    pl21->place(0,0,5,1);
    pl22->place(6,0,3,1);
    pl23->place(10,0,2,1);
    pl24->place(14.5,0,2,1);
    pl25->place(18,0,5,1);


    Hud->initUi("images/heart.png", 0);
    Hud->initUi("images/ammo.png", 1);
    //F->buildFonts((char*)ply->health);

    start = run = clock();

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
            KbMs->keys[wParam] = true;
            if (scne == LV1 && ply->actionTrigger != ply->JUMP) {
                wep->wPos.y = 10.0;

                //keyboard movement for the platforms level 1

                if(KbMs->keyPause() == 1){ //if H key is pressed
                    scne = PAUSE; //pause the game
                }
            }

            else if (scne == LV2 && ply->actionTrigger != ply->JUMP) {
                KbMs->keyPlayer(ply);
                KbMs->keyEnv(prLx[2], 0.005);
                wep->wPos.y = 10.0;

                //keyboard movement for the platforms level 2
                KbMs->keyEnvL1(pl21,0.05);
                KbMs->keyEnvL1(pl22,0.05);
                KbMs->keyEnvL1(pl23,0.05);
                KbMs->keyEnvL1(pl24,0.05);
                KbMs->keyEnvL1(pl25,0.05);

                if(KbMs->keyPause() == 1){ //if H key is pressed
                    scne = PAUSE; //pause the game
                }
            }

            else if (scne == LV3 && ply->actionTrigger != ply->JUMP) {
                KbMs->keyPlayer(ply);
                KbMs->keyEnv(prLx[3], 0.005);
                wep->wPos.y = 10.0;

                if(KbMs->keyPause() == 1){ //if H key is pressed
                    scne = PAUSE; //pause the game
                }
            }

            else if (scne == TITLE) {
                scne = MENU;
            }
            else if (scne == MENU) {
                int temp = KbMs->keyTitle(tl);
                if (temp == 2) {
                    scne = LV1;
                    level = 1;
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
                else if (temp == 6) {
                    scne = LV2;
                    level = 2;
                }
                else if (temp == 7) {
                    scne = LV3;
                    level = 3;
                }
            }
            else if(scne == PAUSE){
                if(KbMs->keyPause() == 1){ //check if ESC key is pressed
                    if (level == 1) //resume game
                        scne = LV1;
                    else if (level == 2)
                        scne = LV2;
                    else if (level == 3)
                        scne = LV3;
                }
                else if(KbMs->keyPause() == 2){
                    scne = MENU; //return to title screen
                }
            }
            break;

        case WM_KEYUP:
            KbMs->keys[wParam] = false;
            if (scne == LV1 || scne == LV2 || scne == LV3) {
                ply->actions(ply->IDLE);
            }
            break;

        case WM_LBUTTONDOWN:
            if (scne == LV1 || scne == LV2 || scne == LV3) {
                KbMs->mouseWhip(wep, ply, LOWORD(lParam), HIWORD(lParam));
            }
            else if (scne == TITLE) {
                scne = MENU;
            }
            break;

        case WM_RBUTTONDOWN:
            if (scne == LV1 || scne == LV2 || scne == LV3) {
                numBullet = ply->ammo - 1;
                if (numBullet >= 0) {
                    ammo[numBullet].placeBullet(ply->pPos);
                    if (ply->playerDir == 'L')
                        ammo[numBullet].act = ammo->MOVEL;
                    else if (ply->playerDir == 'R')
                        ammo[numBullet].act = ammo->MOVER;
                    ply->ammo--;
                }
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
