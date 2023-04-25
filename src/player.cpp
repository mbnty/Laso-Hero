#include "player.h"

player::player()
{
    //ctor
    verts[0].x = -0.5; verts[0].y = -0.5; verts[0].z = -1.0;
    verts[1].x = 0.5; verts[1].y = -0.5; verts[1].z = -1.0;
    verts[2].x = 0.5; verts[2].y = 0.5; verts[2].z = -1.0;
    verts[3].x = -0.5; verts[3].y = 0.5; verts[3].z = -1.0;

    health = 5; //max of 5
    ammo = 3; //max of 6

    runSpeed = 0.01;
    jumpSpeed = 0;
    actionTrigger = IDLE;

    velocity = 65;
    theta = 30 * PI/180.0;
    t = 1;
    start = clock();

    playerDir = 'L';

    pPos.x = 0;
    pPos.y = -0.65;
    pPos.z = -2;
}

player::~player()
{
    //dtor
}

void player::drawPlayer()
{
    tLoad->binder(tex);

    glTranslated(pPos.x, pPos.y, pPos.z);

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
}

void player::playerInit(char* fileName, int vFrm, int hFrm)
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

void player::actions(acts action)
{
    if(action == IDLE){
        if(playerDir == 'R'){
            xMax = 1.0/(float)vFrames;
            xMin = 0.0;
            yMax = 1.0/(float)hFrames;
            yMin = 0.0;
        }
        else if(playerDir == 'L'){
            xMax = 0.0;
            xMin = 1.0/(float)vFrames;
            yMax = 1.0/(float)hFrames;
            yMin = 0.0;
        }
    }
    if(action == WALKR){
        if(playerDir != 'R'){
            float tmp;
            tmp = xMax;
            xMax = xMin;
            xMin = tmp;
            playerDir = 'R';
        }

        playerDir = 'R';
        xMin += 1.0/(float)vFrames;
        xMax += 1.0/(float)vFrames;
        if(xMax > 1){
            xMax = 1.0/(float)vFrames;
            xMin = 0.0;

            yMax += 1.0/(float)hFrames;
            yMin += 1.0/(float)hFrames;
        }
        //pPos.x += runSpeed;
        if(pPos.x >= 2.5){
            pPos.x = 2.5;
        }

        actionTrigger = WALKR;
    }
    if(action == WALKL){
        if(playerDir != 'L'){
            float tmp;
            tmp = xMax;
            xMax = xMin;
            xMin = tmp;
            playerDir = 'L';
        }
        playerDir = 'L';
        xMin += 1.0/(float)vFrames;
        xMax += 1.0/(float)vFrames;

        if(xMin > 1){
            xMax = 0.0/(float)vFrames;
            xMin = 1.0/(float)vFrames;

            yMax += 1.0/(float)hFrames;
            yMin += 1.0/(float)hFrames;
        }
        //pPos.x -= runSpeed;
        if(pPos.x <= -2.5){
            pPos.x = -2.5;
        }

        actionTrigger = WALKL;
    }
    if(action == JUMP){
        yMax = 2.0/(float)hFrames;
        yMin = 1.0/(float)hFrames;

        if (clock() - start > 30) {
            // Calculate jump speed
            jumpSpeed = (velocity * t * sin(theta) - 0.5 * GRVITY * t * t) / 700.0;
            pPos.y += jumpSpeed;

            xMax += 1.0/(float)vFrames;
            xMin += 1.0/(float)vFrames;

            if (playerDir == 'L')
                pPos.x -= runSpeed;
            else if (playerDir == 'R')
                pPos.x += runSpeed;

            if (pPos.y >= -0.65) {      // While in jump animation, update Timer
                t += 0.2;
                actionTrigger = JUMP;   // Update actionTrigger
            }

            else {                      // Once character reaches ground, reset Timer, character y position, and return to idle
                t = 1;
                pPos.y = -0.65;
                actionTrigger = IDLE;   // Update actionTrigger
            }
            start = clock();
        }
    }
    /*
    switch(action)
    {

    case IDLE:
        if(playerDir == 'R'){
            xMax = 1.0/(float)vFrames;
            xMin = 0.0;
            yMax = 1.0/(float)hFrames;
            yMin = 0.0;
        }
        else if(playerDir == 'L'){
            xMax = 0.0;
            xMin = 1.0/(float)vFrames;
            yMax = 1.0/(float)hFrames;
            yMin = 0.0;
        }
        break;

    case WALKR: //walk right
        if(playerDir != 'R'){
            float tmp;
            tmp = xMax;
            xMax = xMin;
            xMin = tmp;
            playerDir = 'R';
        }

        playerDir = 'R';
        xMin += 1.0/(float)vFrames;
        xMax += 1.0/(float)vFrames;
        if(xMax > 1){
            xMax = 1.0/(float)vFrames;
            xMin = 0.0;

            yMax += 1.0/(float)hFrames;
            yMin += 1.0/(float)hFrames;
        }
        //pPos.x += runSpeed;
        if(pPos.x >= 2.5){
            pPos.x = 2.5;
        }

        actionTrigger = WALKR;
        break;

    case WALKL: //walk left
        if(playerDir != 'L'){
            float tmp;
            tmp = xMax;
            xMax = xMin;
            xMin = tmp;
            playerDir = 'L';
        }
        playerDir = 'L';
        xMin += 1.0/(float)vFrames;
        xMax += 1.0/(float)vFrames;

        if(xMin > 1){
            xMax = 0.0/(float)vFrames;
            xMin = 1.0/(float)vFrames;

            yMax += 1.0/(float)hFrames;
            yMin += 1.0/(float)hFrames;
        }
        //pPos.x -= runSpeed;
        if(pPos.x <= -2.5){
            pPos.x = -2.5;
        }

        actionTrigger = WALKL;
        break;

    case JUMP:
        yMax = 2.0/(float)hFrames;
        yMin = 1.0/(float)hFrames;

        if (clock() - start > 30) {
            // Calculate jump speed
            jumpSpeed = (velocity * t * sin(theta) - 0.5 * GRVITY * t * t) / 700.0;
            pPos.y += jumpSpeed;

            xMax += 1.0/(float)vFrames;
            xMin += 1.0/(float)vFrames;

            if (playerDir == 'L')
                pPos.x -= runSpeed;
            else if (playerDir == 'R')
                pPos.x += runSpeed;

            if (pPos.y >= -0.65) {      // While in jump animation, update Timer
                t += 0.2;
                actionTrigger = JUMP;   // Update actionTrigger
            }

            else {                      // Once character reaches ground, reset Timer, character y position, and return to idle
                t = 1;
                pPos.y = -0.65;
                actionTrigger = IDLE;   // Update actionTrigger
            }
            start = clock();
        }

        break;
   }
   */
}
