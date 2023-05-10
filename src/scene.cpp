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
#include <sounds.h>
#include <particles.h>
#include <fonts.h>

model *startModel = new model();
inputs *KbMs = new inputs();
player *ply = new player();
title *tl = new title();
whip* wep = new whip();
checkCollision *hit = new checkCollision();
ui *Hud = new ui();
powerups *spec = new powerups();
particles *sand = new particles();
fonts *F = new fonts();
fonts *Fs = new fonts();

//Enemy Bool Triggers
bool CanHit = false;
bool EnMove = false;
powerups *health = new powerups();
sounds *snds = new sounds();

parallax prLx[10];
bullet ammo[6];

int const enemyCount1 = 5;
enemy spearman[enemyCount1];

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

//objects for the platforms for the second level
platform *pl31 = new platform();
platform *pl32 = new platform();
platform *pl33 = new platform();
platform *pl34 = new platform();
platform *pl35 = new platform();

platform *arrow = new platform();
platform *go = new platform();
platform *horse = new platform();

int numBullet;
int level = 1;
int numOfEn = enemyCount1; //Tracks Amount of Enemies
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
        //snds->playMusic("sounds/menu.mp3");
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        tl->drawTitle(screenWidth, screenHeight);
        glPopMatrix();

        glPushMatrix();
            sand->updateParticles();
            sand->generateParticles(0, 0);
            sand->drawParticles();
        glPopMatrix();
    }

    else if(scne == HELP){
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        prLx[5].drawSquare(screenWidth, screenHeight);
        glPopMatrix();
    }

    else if(scne == CREDITS){
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        prLx[6].drawSquare(screenWidth, screenHeight);
        glPopMatrix();
    }

    else if(scne == CONTROLS){
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        prLx[7].drawSquare(screenWidth, screenHeight);
        glPopMatrix();
    }

    else if (scne == QUIT) {
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        tl->drawMenu(screenWidth, screenHeight);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-2.0, -2.0, 0);
        tl->drawSquare(screenWidth, screenHeight, 6);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(2.0, -2.0, 0);
        tl->drawSquare(screenWidth, screenHeight, 7);
        glPopMatrix();

        glPushMatrix();
            sand->updateParticles();
            sand->generateParticles(0, 0);
            sand->drawParticles();
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

        glPushMatrix();
            sand->updateParticles();
            sand->generateParticles(0, 0);
            sand->drawParticles();
        glPopMatrix();
    }

    else if (scne == LV1) {
        //snds->playSound("sounds/sound1.mp3");

        if (ply->health == 0){      // Close program once player dies *CHANGE LATER*
            //PostQuitMessage(0);
        }

        //matrix for the background parallax
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        prLx[level].drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        if (numOfEn == 0) {           // Spawn horse once all enemies are killed
            horse->alpha = 1.0;
            go->drawPlatform();
            horse->drawPlatform();
        }

        if(!F->run){ //displays number of enemies remaining
            F->pos.y = 0.64;
            F->buildFonts(F->getZero(numOfEn));
            Fs->buildFonts(Fs->getTens(numOfEn));
            F->run = true;
            Fs->run = true;
        }

        glPushMatrix();
        glScalef(0.05, 0.07, 1);
        glTranslatef(13.4, 7.5, -1.9);
        prLx[8].drawPopUp(524, 93);
        glPopMatrix();

        // draw hud
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

        // this martix holds the platforms
        glPushMatrix();
        pl1->drawPlatform();
        pl2->drawPlatform();
        pl3->drawPlatform();
        pl4->drawPlatform();
        pl5->drawPlatform();

        sp1->drawPlatform();
        sp2->drawPlatform();
        sp3->drawPlatform();

        arrow->drawPlatform();
        glPopMatrix();

        arrow->alpha -= 0.005;
        if (arrow->alpha <= 0)
            arrow->alpha = 1.0;

        go->alpha -= 0.005;
        if (go->alpha <= 0)
            go->alpha = 1.0;

        // draw bullet
        for (int i = 0; i < 6; i++) {
            glPushMatrix();
            ammo[i].drawBullet();
            glPopMatrix();

            if (ammo[i].bPos.x >= 3 || ammo[i].bPos.x <= -3)
                ammo[i].act = ammo->IDLE;
        }

        // draw player
        if (ply->pColor.y < 1) {
            ply->pColor.y += 0.003;
            ply->pColor.z += 0.003;
        }

        if (ply->actionTrigger == ply->JUMP)
            ply->actions(ply->JUMP,snds, sand);
        else if (ply->isIdle)
            ply->actions(ply->IDLE,snds, sand);

        sand->updateJumpParticles(1);
        sand->drawParticles();

        glPushMatrix();
        ply->drawPlayer();
        glPopMatrix();

        // draw enemies
        for(int i = 0; i < enemyCount1; i++){

            spearman[i].enemyAIManager(ply);

            if (!spearman[i].isDead && hit->isQuadCollisionEnemy(ply, spearman[i]) && clock() - ply->damage > 2000) {
                ply->pColor.y = 0; ply->pColor.z = 0;
                ply->health--;
                ply->damage = clock();
            }

            for (int j = 0; j < 6; j++) { //Gun
                if (!spearman[i].isDead) {
                    if (hit->isRadialCollision(ammo[j].bPos.x, spearman[i].enemyPosition.x, ammo[j].bPos.y, spearman[i].enemyPosition.y, 0.1, 0.5)) {
                        spearman[i].movement = spearman->HURT;
                        spearman[i].enHP -= 2; //Gun Does more damage
                        if(spearman[i].enHP <= 0){
                            spearman[i].movement = spearman->DIE;
                            numOfEn--;
                            F->pos.y = 0.6;
                            F->buildFonts(F->getZero(numOfEn));
                            Fs->buildFonts(Fs->getTens(numOfEn));

                            spec->dropBullet(spearman[i].enemyPosition);
                            spec->act = spec->IDLE;

                            health->dropHealth(spearman[i].enemyPosition);
                            health->act = health->IDLE;
                        }
                        ammo[j].act = ammo->IDLE;
                    }
                }
            }
            if (wep->run == true) { //Whip
                if (!spearman[i].isDead) {
                    if (hit->isQuadCollisionWhip(wep, spearman[i])) {
                        spearman[i].movement = spearman->HURT;
                        spearman[i].enHP--;
                        if(spearman[i].enHP <= 0){
                            spearman[i].movement = spearman->DIE;
                            numOfEn--;
                            F->pos.y = 0.6;
                            F->buildFonts(F->getZero(numOfEn));
                            Fs->buildFonts(Fs->getTens(numOfEn));
                            spec->dropBullet(spearman[i].enemyPosition);
                            spec->act = spec->IDLE;

                            health->dropHealth(spearman[i].enemyPosition);
                            health->act = health->IDLE;
                        }
                        wep->wPos.y = 10.0;
                    }
                }
            }

            if(spearman[i].isSpawn == true){
                spearman[i].drawEnemy();
                spearman[i].actions();
            }
        }
        /*
        int ECount = enemyCount1;
        for(int i = enemyCount1; i > 0; i--){
            if(spearman[i].movement == spearman->DIE){
                ECount--;
                F->pos.y = 0.6;
                F->buildFonts(F->getZero(ECount));
                Fs->buildFonts(Fs->getTens(ECount));
            }
        }*/


        // Draw drops
        if(hit->isQuadCollisionPowerUp(ply, spec) && (ply->ammo < ply->MAX_AMMO)){
            ply->ammo++;
            spec->act = spec->PICKUP;
            spec->actions();
            snds->playSound("sounds/item1.mp3");
        }

        if(hit->isQuadCollisionPowerUp(ply, health) && (ply->health < ply->MAX_HEALTH)){
            ply->health++;
            health->act = health->PICKUP;
            health->actions();
            snds->playSound("sounds/item.mp3");
        }

        glPushMatrix();
        spec->drawSquare();
        glPopMatrix();

        glPushMatrix();
        health->drawSquare();
        glPopMatrix();

        //check if collision with top of platform 1
        if ((ply->pPos.y ) >= (pl1->pos.y +(0.25 * pl1->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl1))
        {
            ply->onPlat = true;
            ply->groundValue = (pl1->pos.y +(0.25 * pl1->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 2
        else if ((ply->pPos.y ) >= (pl2->pos.y +(0.25 * pl2->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl2))
        {
            ply->onPlat = true;
            ply->groundValue = (pl2->pos.y +(0.25 * pl2->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 3
        else if ((ply->pPos.y ) >= (pl3->pos.y +(0.25 * pl3->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl3))
        {
            ply->onPlat = true;
            ply->groundValue = (pl3->pos.y +(0.25 * pl3->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 4
        else if ((ply->pPos.y ) >= (pl4->pos.y +(0.25 * pl4->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl4))
        {
            ply->onPlat = true;
            ply->groundValue = (pl4->pos.y +(0.25 * pl4->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 5
        else if ((ply->pPos.y ) >= (pl5->pos.y +(0.25 * pl5->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl5))
        {
            ply->onPlat = true;
            ply->groundValue = (pl5->pos.y +(0.25 * pl5->scaleSize.y)) + 0.4;
        }

        //case for falling off platform
        else if (ply->onPlat == true)
        {
            ply->t = 8.2;
            ply->groundValue = -0.65;
            ply->actions(ply->JUMP,snds, sand);
        }

        //check if collision with spikes
        if (hit->isQuadCollisionPlatform(ply,sp1) && clock() - ply->damage > 2000)
        {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
            snds->playSound("sounds/hurt.mp3");
        }

        if (hit->isQuadCollisionPlatform(ply,sp2) && clock() - ply->damage > 2000)
        {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
            snds->playSound("sounds/hurt.mp3");
        }

        if (hit->isQuadCollisionPlatform(ply,sp3) && clock() - ply->damage > 2000)
        {
            ply->pColor.y = 0; ply->pColor.z = 0;
            ply->health--;
            ply->damage = clock();
            snds->playSound("sounds/hurt.mp3");
        }

        if (numOfEn == 0 && hit->isLinearCollision(ply->pPos.x, horse->pos.x))       // Move to level 2 once reach horse
        {
            arrow->place(-4.8, 0, 1.5, 1);
            spec->act = spec->IDLE;
            health->act = health->IDLE;
            numOfEn = 5;
            level++;
            horse->alpha = 0.0;
            scne = LV2;
        }

        // draw whip
        glPushMatrix();
        wep->drawWhip();
        glPopMatrix();

        if (wep->run == true) {
            if (wep->t < 1 && clock() - start > 10) {
                wep->t += 0.05;
                start = clock();
            }
            else if (wep->t >= 1 && clock() - start > 120) {
                wep->wPos.y = 10.0;
                wep->run = false;
            }
        }

        for(int i, j = 0; i < F->cCnt, j < Fs->cCnt; i++, j++){
            F->drawFonts(i, 0.04);
            Fs->drawFonts(j, 0);
        }

        // Change scene if input
        if (clock() - run > 30) {
            KbMs->keyPlayer(ply, snds, sand);

            if ((pl1->pos.x < 3.0 || (!KbMs->keys[VK_LEFT] && !KbMs->keys[0x41])) && (pl5->pos.x > -5.0 || (!KbMs->keys[VK_RIGHT] && !KbMs->keys[0x44]))) {
                KbMs->keyEnv(prLx[1], 0.005);
                for (int i = 0; i < enemyCount1; i++)
                    KbMs->keyEnemy(spearman[i]);

                KbMs->keyEnvL1(pl1,0.05);
                KbMs->keyEnvL1(pl2,0.05);
                KbMs->keyEnvL1(pl3,0.05);
                KbMs->keyEnvL1(pl4,0.05);
                KbMs->keyEnvL1(pl5,0.05);

                KbMs->keyEnvL1(sp1,0.05);
                KbMs->keyEnvL1(sp2,0.05);
                KbMs->keyEnvL1(sp3,0.05);

                KbMs->keyEnvL1(arrow, 0.05);
                KbMs->keyEnvL1(horse, 0.05);

                KbMs->keyPowerUp(spec, 0.05);
                KbMs->keyPowerUp(health, 0.05);
            }
            run = clock();
        }
    }

    else if (scne == LV2) {
        if (ply->health == 0) {      // Close program once player dies *CHANGE LATER*
            //PostQuitMessage(0);
        }

        //matrix for the background parallax
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        prLx[level].drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        if (numOfEn == 0) {           // Spawn horse once all enemies are killed
            horse->alpha = 1.0;
            go->drawPlatform();
            horse->drawPlatform();
        }

        // draw hud
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
        arrow->drawPlatform();
        glPopMatrix();

        arrow->alpha -= 0.005;
        if (arrow->alpha <= 0)
            arrow->alpha = 1.0;

        go->alpha -= 0.005;
        if (go->alpha <= 0)
            go->alpha = 1.0;

        // draw bullet
        for (int i = 0; i < 6; i++) {
            glPushMatrix();
            ammo[i].drawBullet();
            glPopMatrix();

            if (ammo[i].bPos.x >= 3 || ammo[i].bPos.x <= -3)
                ammo[i].act = ammo->IDLE;
        }

        // draw player
        if (ply->pColor.y < 1) {
            ply->pColor.y += 0.003;
            ply->pColor.z += 0.003;
        }

        if (ply->actionTrigger == ply->JUMP)
            ply->actions(ply->JUMP,snds, sand);
        else if (ply->isIdle)
            ply->actions(ply->IDLE,snds, sand);

        glPushMatrix();
        ply->drawPlayer();
        glPopMatrix();

        sand->updateJumpParticles(2);
        sand->drawParticles();

        // Draw drops
        if(hit->isQuadCollisionPowerUp(ply, spec) && (ply->ammo < ply->MAX_AMMO)){
            ply->ammo++;
            spec->act = spec->PICKUP;
            spec->actions();
        }

        if(hit->isQuadCollisionPowerUp(ply, health) && (ply->health < ply->MAX_HEALTH)){
            ply->health++;
            health->act = health->PICKUP;
            health->actions();
        }

        glPushMatrix();
        spec->drawSquare();
        glPopMatrix();

        glPushMatrix();
        health->drawSquare();
        glPopMatrix();

        //check if collision with top of platform 1
        if ((ply->pPos.y ) >= (pl21->pos.y +(0.25 * pl21->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl21))
        {
            ply->onPlat = true;
            ply->groundValue = (pl21->pos.y +(0.25 * pl21->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 2
        else if ((ply->pPos.y ) >= (pl22->pos.y +(0.25 * pl22->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl22))
        {
            ply->onPlat = true;
            ply->groundValue = (pl22->pos.y +(0.25 * pl22->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 3
        else if ((ply->pPos.y ) >= (pl23->pos.y +(0.25 * pl23->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl23))
        {
            ply->onPlat = true;
            ply->groundValue = (pl23->pos.y +(0.25 * pl23->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 4
        else if ((ply->pPos.y ) >= (pl24->pos.y +(0.25 * pl24->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl24))
        {
            ply->onPlat = true;
            ply->groundValue = (pl24->pos.y +(0.25 * pl24->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 5
        else if ((ply->pPos.y ) >= (pl25->pos.y +(0.25 * pl25->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl25))
        {
            ply->onPlat = true;
            ply->groundValue = (pl25->pos.y +(0.25 * pl25->scaleSize.y)) + 0.4;
        }

        //case for falling off platform
        else if (ply->onPlat == true)
        {
            ply->t = 8.2;
            ply->groundValue = -0.65;
            ply->actions(ply->JUMP,snds, sand);
        }

        if (numOfEn == 0 && hit->isLinearCollision(ply->pPos.x, horse->pos.x))       // Move to level 2 once reach horse
        {
            arrow->place(-4.8, 0, 1.5, 1);
            spec->act = spec->IDLE;
            health->act = health->IDLE;
            numOfEn = 5;
            level++;
            horse->alpha = 0.0;
            scne = LV3;
        }

        // draw whip
        glPushMatrix();
        wep->drawWhip();
        glPopMatrix();

        if (wep->run == true && clock() - start > 10) {
            if (wep->t < 1) {
                wep->t += 0.05;
                start = clock();
            }
            else if (wep->t >= 1 && clock() - start > 120) {
                wep->wPos.y = 10.0;
                wep->run = false;
            }
        }

        // Change scene if input
        if (clock() - run > 30) {
            KbMs->keyPlayer(ply, snds, sand);

            if ((pl21->pos.x < 3.0 || !KbMs->keys[VK_LEFT] && !KbMs->keys[0x41]) && (pl25->pos.x > -5.0 || (!KbMs->keys[VK_RIGHT] && !KbMs->keys[0x44]))) {
                KbMs->keyEnv(prLx[2], 0.005);

                KbMs->keyEnvL1(pl21,0.05);
                KbMs->keyEnvL1(pl22,0.05);
                KbMs->keyEnvL1(pl23,0.05);
                KbMs->keyEnvL1(pl24,0.05);
                KbMs->keyEnvL1(pl25,0.05);

                KbMs->keyEnvL1(arrow, 0.05);

                KbMs->keyPowerUp(spec, 0.05);
                KbMs->keyPowerUp(health, 0.05);
            }
            run = clock();
        }
    }

    else if (scne == LV3) {
        if (ply->health == 0) {      // Close program once player dies *CHANGE LATER*
            //PostQuitMessage(0);
        }

        if (numOfEn == 0) {
            //horse->alpha = 1.0;
        }

        //matrix for the background parallax
        glPushMatrix();
        glScaled(4.2, 4.2, 1.0);
        prLx[level].drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        // draw hud
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
        pl31->drawPlatform();
        pl32->drawPlatform();
        pl33->drawPlatform();
        pl34->drawPlatform();
        pl35->drawPlatform();
        arrow->drawPlatform();
        glPopMatrix();

        arrow->alpha -= 0.005;
        if (arrow->alpha <= 0)
            arrow->alpha = 1.0;

        // draw bullet
        for (int i = 0; i < 6; i++) {
            glPushMatrix();
            ammo[i].drawBullet();
            glPopMatrix();

            if (ammo[i].bPos.x >= 3 || ammo[i].bPos.x <= -3)
                ammo[i].act = ammo->IDLE;
        }

        // draw player
        if (ply->pColor.y < 1) {
            ply->pColor.y += 0.003;
            ply->pColor.z += 0.003;
        }

        if (ply->actionTrigger == ply->JUMP)
            ply->actions(ply->JUMP,snds, sand);
        else if (ply->isIdle)
            ply->actions(ply->IDLE,snds, sand);

        glPushMatrix();
        ply->drawPlayer();
        glPopMatrix();

        sand->updateJumpParticles(3);
        sand->drawParticles();

        // Draw drops
        if(hit->isQuadCollisionPowerUp(ply, spec) && (ply->ammo < ply->MAX_AMMO)){
            ply->ammo++;
            spec->act = spec->PICKUP;
            spec->actions();
        }

        if(hit->isQuadCollisionPowerUp(ply, health) && (ply->health < ply->MAX_HEALTH)){
            ply->health++;
            health->act = health->PICKUP;
            health->actions();
        }

        glPushMatrix();
        spec->drawSquare();
        glPopMatrix();

        glPushMatrix();
        health->drawSquare();
        glPopMatrix();

        //check if collision with top of platform 1
        if ((ply->pPos.y ) >= (pl31->pos.y +(0.25 * pl31->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl31))
        {
            ply->onPlat = true;
            ply->groundValue = (pl31->pos.y +(0.25 * pl31->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 2
        else if ((ply->pPos.y ) >= (pl32->pos.y +(0.25 * pl32->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl32))
        {
            ply->onPlat = true;
            ply->groundValue = (pl32->pos.y +(0.25 * pl32->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 3
        else if ((ply->pPos.y ) >= (pl33->pos.y +(0.25 * pl33->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl33))
        {
            ply->onPlat = true;
            ply->groundValue = (pl33->pos.y +(0.25 * pl33->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 4
        else if ((ply->pPos.y ) >= (pl34->pos.y +(0.25 * pl34->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl34))
        {
            ply->onPlat = true;
            ply->groundValue = (pl34->pos.y +(0.25 * pl34->scaleSize.y)) + 0.4;
        }

        //check if collision with top of platform 5
        else if ((ply->pPos.y ) >= (pl35->pos.y +(0.25 * pl35->scaleSize.y)) && hit->isQuadCollisionPlatform(ply,pl35))
        {
            ply->onPlat = true;
            ply->groundValue = (pl35->pos.y +(0.25 * pl35->scaleSize.y)) + 0.4;
        }

        //case for falling off platform
        else if (ply->onPlat == true)
        {
            ply->t = 8.2;
            ply->groundValue = -0.65;
            ply->actions(ply->JUMP,snds, sand);
        }

        if (numOfEn == 0 && hit->isLinearCollision(ply->pPos.x, horse->pos.x))
        {

        }

        // draw whip
        glPushMatrix();
        wep->drawWhip();
        glPopMatrix();

        if (wep->run == true && clock() - start > 10) {
            if (wep->t < 1) {
                wep->t += 0.01;
                start = clock();
            }
            else if (wep->t >= 1 && clock() - start > 120) {
                wep->wPos.y = 10.0;
                wep->run = false;
            }
        }

        // Change scene if input
        if (clock() - run > 30) {
            KbMs->keyPlayer(ply, snds, sand);

            if ((pl31->pos.x < 3.0 || !KbMs->keys[VK_LEFT] && !KbMs->keys[0x41]) && (pl35->pos.x > -5.0 || (!KbMs->keys[VK_RIGHT] && !KbMs->keys[0x44]))) {
                KbMs->keyEnv(prLx[3], 0.005);

                KbMs->keyEnvL1(pl31,0.05);
                KbMs->keyEnvL1(pl32,0.05);
                KbMs->keyEnvL1(pl33,0.05);
                KbMs->keyEnvL1(pl34,0.05);
                KbMs->keyEnvL1(pl35,0.05);

                KbMs->keyEnvL1(arrow, 0.05);

                KbMs->keyPowerUp(spec, 0.05);
                KbMs->keyPowerUp(health, 0.05);
            }
            run = clock();
        }
    }


    else if(scne == PAUSE){
        glPushMatrix(); //matrix for the background parallax
        glScaled(4.2, 4.2, 1.0);
        prLx[level].drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        glPushMatrix();
        glScalef(0.4, 0.5, 1);
        glTranslatef(0, 0, -1.9);
        prLx[4].drawPopUp(screenWidth, screenHeight);
        glPopMatrix();

        glPushMatrix();
        glScalef(0.05, 0.07, 1);
        glTranslatef(13.4, 7.5, -1.9);
        prLx[8].drawPopUp(524, 93);
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

        glPushMatrix();
        ply->drawPlayer();
        glPopMatrix();

        glPushMatrix();
        wep->drawWhip();
        glPopMatrix();

        for(int i, j = 0; i < F->cCnt, j < Fs->cCnt; i++, j++){
            F->drawFonts(i, 0.04);
            Fs->drawFonts(j, 0);
        }

        if (level == 1) {
            glPushMatrix(); // this martix holds the platforms
            pl1->drawPlatform();
            sp1->drawPlatform();
            pl2->drawPlatform();
            pl3->drawPlatform();
            sp2->drawPlatform();
            pl4->drawPlatform();
            pl5->drawPlatform();
            sp3->drawPlatform();
            arrow->drawPlatform();
            horse->drawPlatform();
            go->drawPlatform();
            glPopMatrix();

            for (int i = 0; i < enemyCount1; i++) {
                if (!spearman[i].isDead) {
                    spearman[i].drawEnemy();
                }
            }
        }

        else if (level == 2) {
            glPushMatrix();
            pl21->drawPlatform();
            pl22->drawPlatform();
            pl23->drawPlatform();
            pl24->drawPlatform();
            pl25->drawPlatform();
            arrow->drawPlatform();
            go->drawPlatform();
            horse->drawPlatform();
            glPopMatrix();
        }

        else if (level == 3) {
            glPushMatrix();
            pl31->drawPlatform();
            pl32->drawPlatform();
            pl33->drawPlatform();
            pl34->drawPlatform();
            pl35->drawPlatform();
            arrow->drawPlatform();
            go->drawPlatform();
            horse->drawPlatform();
            glPopMatrix();
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

    for(int i = 0; i < enemyCount1; i++){
        glGenTextures(10, spearman[i].texInd);
        spearman[i].setAsSpear();
        spearman[i].placeEnemy(pos3{i + 2.0, -0.25, -2.0});
    }

    prLx[1].initParallax("images/background1.jpg"); //initializing parallax with background image
    prLx[2].initParallax("images/background2.jpg");
    prLx[3].initParallax("images/background3.png");
    prLx[4].initPopUp("images/Pause.png"); //pause screen popup
    prLx[5].initParallax("images/helpScreen.png"); //help screen
    prLx[6].initParallax("images/creditScreen.png"); //credits screen
    prLx[7].initParallax("images/controlScreen.png"); //control screen

    tl->initTitle("images/title.png", 0);
    tl->initTitle("images/menu.png", 1);
    tl->initTitle("images/start.png", 2);
    tl->initTitle("images/help.png", 3);
    tl->initTitle("images/credit.png", 4);
    tl->initTitle("images/stop.png", 5);
    tl->initTitle("images/stop.png", 6);
    tl->initTitle("images/start.png", 7);

    ammo[0].projTexture("images/bullet.png");
    for (int i = 0; i < 6; i++) {
        ammo[i].initBullet(ammo[0].tex);
    }

    spec->powTexture("images/ammo.png");
    spec->initPowerUp(spec->powTex);
    health->powTexture("images/heart.png");
    health->initPowerUp(health->powTex);

    wep->initWhip("images/whip.png");

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
    pl2->place(6,0,3,1);
    pl3->place(10,0,2,1);
    pl4->place(11.5,0,2,1);
    pl5->place(18,0,5,1);

    sp1->place(1,-1.0,1,0.5);
    sp2->place(11,-1.0,1,0.5);
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

    //level 3
    pl31->initPlatform("images/platform3.png",1,1);
    pl32->initPlatform("images/platform3.png",1,1);
    pl33->initPlatform("images/platform3.png",1,1);
    pl34->initPlatform("images/platform3.png",1,1);
    pl35->initPlatform("images/platform3.png",1,1);

    pl31->place(0,0,5,1);
    pl32->place(6,0,3,1);
    pl33->place(10,0,2,1);
    pl34->place(14.5,0,2,1);
    pl35->place(18,0,5,1);

    arrow->initPlatform("images/right.png", 1, 1);
    arrow->place(-4.8, 0, 1.5, 1);

    go->initPlatform("images/right.png", 1, 1);
    go->place(0.0, 0.0, 1.0, 0.5);

    horse->initPlatform("images/horse.png", 1, 1);
    horse->alpha = 0.0;
    horse->place(22, -0.7, 2, 2);

    Hud->initUi("images/heart.png", 0);
    Hud->initUi("images/ammo.png", 1);

    prLx[8].initPopUp("images/enemyCounter.png");

    F->initFonts("images/numbers.png");
    Fs->initFonts("images/numbers.png");

    sand->generateParticles(0, 0);

    snds->initSound();

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
            if (scne == LV1 || scne == LV2 || scne == LV3) {
                if (wParam == VK_UP || wParam == 0x57) {
                    ply->actions(ply->JUMP,snds, sand);
                }

                if(KbMs->keyPause() == 1){ //if H key is pressed
                    scne = PAUSE; //pause the game
                }
            }

            else if (scne == TITLE) {
                tl->selection = 2;
                scne = MENU;
            }
            else if (scne == MENU) {
                int temp = KbMs->keyTitle(tl);
                cout << temp << endl;
                if (temp == 2) {
                    sand->resetParticles();
                    if (level == 1)
                        scne = LV1;
                    else if (level == 2)
                        scne = LV2;
                    else if (level == 3)
                        scne = LV3;
                }
                else if (temp == 3) {
                    scne = HELP;
                }
                else if (temp == 4) {
                    scne = CREDITS;
                }
                else if (temp == 5) {
                    tl->selection = 3;
                    scne = QUIT;
                }
                else if (temp == 6) {
                    scne = LV2;
                    level = 2;
                    sand->resetParticles();
                }
                else if (temp == 7) {
                    scne = LV3;
                    level = 3;
                    sand->resetParticles();
                }
            }

            else if(scne == HELP){
                if(KbMs->keyPause() == 2){ //if M is pressed
                    scne = MENU;
                }
                if(KbMs->keyPause() == 3){ //if C is pressed
                    scne = CONTROLS;
                }
            }

            else if(scne == CONTROLS){
                if(KbMs->keyPause() == 2){ //if M is pressed
                    scne = MENU;
                }
            }

            else if(scne == CREDITS){
                if(KbMs->keyPause() == 2){ //if M is pressed
                    scne = MENU;
                }
            }

            else if (scne == QUIT) {
                int temp = KbMs->keyQuit(tl);
                cout << temp << endl;
                if (temp == 6) {
                    PostQuitMessage(0);
                }
                else if (temp == 7) {
                    tl->selection = 2;
                    scne = MENU;
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
                ply->actions(ply->IDLE,snds, sand);
            }
            break;

        case WM_LBUTTONDOWN:
            if (scne == LV1 || scne == LV2 || scne == LV3) {
                KbMs->mouseWhip(wep, ply, LOWORD(lParam), HIWORD(lParam),snds);
            }
            else if (scne == TITLE) {
                scne = MENU;
            }
            break;

        case WM_RBUTTONDOWN:
            if (scne == LV1 || scne == LV2 || scne == LV3) {
                numBullet = ply->ammo - 1;
                if (numBullet >= 0) {
                    snds->playSound("sounds/shot.mp3");
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
