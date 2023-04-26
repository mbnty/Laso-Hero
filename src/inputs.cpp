#include "inputs.h"

inputs::inputs()
{
    //ctor
}

inputs::~inputs()
{
    //dtor
}

void inputs::getRealMouse(int x, int y) {
    GLint viewPort[4];
    GLdouble modelView[16];
    GLdouble projectionMat[16];
    GLfloat winX, winY, winZ;

    glGetDoublev(GL_PROJECTION_MATRIX, projectionMat);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
    glGetIntegerv(GL_VIEWPORT, viewPort);

    winX = (GLfloat)x;
    winY = (GLfloat)viewPort[3] - (GLfloat)y;

    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelView, projectionMat, viewPort, &realX, &realY, &realZ);
}

void inputs::keyModel(model*)
{
    switch(wParam) {
        case VK_LEFT:       // Action for model by pressing "Left" key
            break;

        case VK_RIGHT:      // Action for model by pressing "Right" key
            break;

        case VK_UP:         // Action for model by pressing "Up" key
            break;

        case VK_DOWN:       // Action for model by pressing "Down" key
            break;
    }
}

void inputs::keyPlayer(player* ply)
{
    if(keys[VK_LEFT] || keys[0x41]){
        ply->actions(ply->WALKL);
    }
    if(keys[VK_RIGHT] || keys[0x44]){
        ply->actions(ply->WALKR);
    }
    if(keys[VK_UP] || keys[VK_SPACE] && ply->actionTrigger != ply->JUMP){
         ply->actions(ply->JUMP);
    }
    /*
    switch(wParam) {
        case VK_LEFT:       // Action for player by pressing "Left" key and "A" key
        case 0x41:
            cout << "Left" << endl;
            ply->actions(ply->WALKL);
            break;

        case VK_RIGHT:      // Action for player by pressing "Right" key and "D" key
        case 0x44:
            cout << "Right" << endl;
            ply->actions(ply->WALKR);
            break;

        case VK_UP:         // Action for player by pressing "Up" key and "W" key
        case 0x57:
            ply->actions(ply->JUMP);
            break;

        case VK_DOWN:       // Action for player by pressing "Down" key and "S" key
        case 0x53:
            break;
    }
    */
}

void inputs::mousePlayer()
{
    switch(wParam) {
        case VK_LEFT:       // Action for player by pressing "Left" key and "A" key
        case 0x41:
            break;

        case VK_RIGHT:      // Action for player by pressing "Right" key and "D" key
        case 0x44:
            break;

        case VK_UP:         // Action for player by pressing "Up" key and "W" key
        case 0x57:
            break;

        case VK_DOWN:       // Action for player by pressing "Down" key and "S" key
        case 0x53:
            break;
    }
}

void inputs::keyEnv(parallax& plx, float speed)
{
    if (keys[VK_LEFT]) {
        plx.xMax -= speed;
        plx.xMin -= speed;
    }

    if (keys[VK_RIGHT]) {
        plx.xMax += speed;
        plx.xMin += speed;
    }
/*
        case VK_UP:
            //plx->yMax -=speed;
            //plx->yMin -=speed;
            break;

        case VK_DOWN:
            //plx->yMax += speed;
            //plx->yMin += speed;
            break;

    }*/
}

int inputs::keyPause()
{
    switch(wParam)
    {
        case 0x48: //check if H key is pressed
            return 1;
            break;

        case 0x4D:
            return 2; //check if M key is pressed
            break;
    }
}

void inputs::keyEnemy(enemy* en)
{
    if(keys[VK_RIGHT]){
        en->enemyPosition.x -= en->enemySpeed.x;
    }
    if(keys[VK_LEFT]){
        en->enemyPosition.x += en->enemySpeed.x;
    }
}

int inputs::keyTitle(title* tl)
{
    switch(wParam) {
        case VK_DOWN:
            if (tl->selection < 5) {
                tl->selection++;
            }
            break;

        case VK_UP:
            if (tl->selection > 2) {
                tl->selection--;
            }
            break;

        case VK_SPACE:
            if (tl->selection >= 2 && tl->selection <= 5) {
                return tl->selection;
            }
            break;

        case VK_NUMPAD1:
            return 2;
            break;
        case VK_NUMPAD2:
            return 6;
            break;
        case VK_NUMPAD3:
            return 7;
            break;
    }
    return 0;
}

void inputs::keyWhip(whip* wep, player* ply)
{
    switch(wParam) {
        case VK_SPACE:
            break;
    }
}

void inputs::keyBullet(bullet* ammo, player* ply)
{
    if (wParam == VK_SPACE) {
        int n = ply->ammo - 1;
        if (n >= 0) {
            ammo[n].placeBullet(ply->pPos);
            if (ply->playerDir == 'L')
                ammo[n].act = ammo->MOVEL;
            else if (ply->playerDir == 'R')
                ammo[n].act = ammo->MOVER;
            ply->ammo--;
        }
    }
}

void inputs::keyUp()
{

}

void inputs::mouseWhip(whip* wep, player* ply, double x, double y)
{
    prev_Mx = x;
    prev_My = y;

    switch(wParam) {
        case MK_LBUTTON:
            /*
            wep->wPos.x = ply->pPos.x;
            wep->wPos.y = ply->pPos.y;
            wep->wPos.z = ply->pPos.z;
            getRealMouse(x, y);
            wep->wEnd.x = realX;
            wep->wEnd.y = realY + 2.6;
            wep->wEnd.z = realZ;
            cout << wep->wEnd.x << " " << wep->wEnd.y << " " << wep->wEnd.z << endl;
            */

            wep->wPos.x = ply->pPos.x;
            wep->wPos.y = ply->pPos.y;
            wep->wPos.z = ply->pPos.z;
            if (ply->playerDir == 'L') {
                wep->wEnd.x = -3.0;
                wep->wEnd.y = 1.0;
            }
            else if (ply->playerDir == 'R') {
                wep->wEnd.x = 3.0;
                wep->wEnd.y = 1.0;
            }
            wep->run = true;
            break;

        case MK_RBUTTON:
            break;

        case MK_MBUTTON:
            break;
    }
}

void inputs::mouseMove(double x, double y)
{
    prev_Mx = x;
    prev_My = y;
}

void inputs::updateWParam(WPARAM param)
{
    wParam = param;
}

void inputs::keyEnvL1(platform* p, float speed)
{
    if (keys[VK_LEFT] || keys[0x41]) {
        p->pos.x += speed;
    }

    if (keys[VK_RIGHT] || keys[0x44]) {
        p->pos.x -= speed;
    }
/*
        case VK_UP:
            //plx->yMax -=speed;
            //plx->yMin -=speed;
            break;

        case VK_DOWN:
            //plx->yMax += speed;
            //plx->yMin += speed;
            break;

    }*/
}

void inputs::keyPowerUp(powerups* pow, float speed)
{
    if (keys[VK_LEFT] || keys[0x41]) {
        pow->powPos.x += speed;
    }

    if (keys[VK_RIGHT] || keys[0x44]) {
        pow->powPos.x -= speed;
    }
/*
        case VK_UP:
            //plx->yMax -=speed;
            //plx->yMin -=speed;
            break;

        case VK_DOWN:
            //plx->yMax += speed;
            //plx->yMin += speed;
            break;

    }*/
}

