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

void inputs::keyPlayer(player* ply, sounds *sds, particles* sand)
{
    if(keys[VK_LEFT] || keys[0x41]){
        ply->actions(ply->WALKL,sds, sand);
    }

    if(keys[VK_RIGHT] || keys[0x44]){
        ply->actions(ply->WALKR,sds, sand);
    }
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
    if (keys[VK_LEFT] || keys[0x41]) {
        plx.xMax -= speed;
        plx.xMin -= speed;
    }

    if (keys[VK_RIGHT] || keys[0x44]) {
        plx.xMax += speed;
        plx.xMin += speed;
    }
}

int inputs::keyPause()
{
    switch(wParam)
    {
        case 0x48: //check if H key is pressed
            return 1;
            break;

        case 0x4D: //check if M key is pressed
            return 2;
            break;

        case 0x43: //check if C key is pressed
            return 3;
            break;

        case 0x52: //check if R key is pressed
            return 4;
            break;
    }
}

void inputs::keyEnemy(enemy& en)
{
    if (keys[VK_RIGHT] || keys[0x44]) {
        en.enemyPosition.x -= en.enemySpeed.x;
    }
    if (keys[VK_LEFT] || keys[0x41]){
        en.enemyPosition.x += en.enemySpeed.x;
    }
}

int inputs::keyTitle(title* tl,sounds* sds)
{
    switch(wParam) {
        case VK_DOWN:
        case 0x53:
            sds->playSound("sounds/select.mp3");
            if (tl->selection < 5) {
                tl->selection++;
            }
            break;

        case VK_UP:
        case 0x57:
            sds->playSound("sounds/select.mp3");
            if (tl->selection > 2) {
                tl->selection--;
            }
            break;

        case VK_SPACE:
        case VK_RETURN:
            sds->playSound("sounds/select.mp3");
            if (tl->selection >= 2 && tl->selection <= 5) {
                return tl->selection;
            }
            break;

        case VK_NUMPAD1:
            return 8;
            break;
        case VK_NUMPAD2:
            return 6;
            break;
        case VK_NUMPAD3:
            return 7;
            break;
        case VK_NUMPAD4:
            return 9;
            break;
    }
    return 0;
}

int inputs::keyQuit(title* tl,sounds* sds) {
    switch(wParam) {
        case VK_LEFT:
        case 0x41:
            sds->playSound("sounds/select.mp3");
            tl->selection = 6;
            break;

        case VK_RIGHT:
        case 0x44:
            sds->playSound("sounds/select.mp3");
            tl->selection = 7;
            break;

        case VK_SPACE:
        case VK_RETURN:
            sds->playSound("sounds/select.mp3");
            return tl->selection;
            break;
    }
}

void inputs::keyWhip(whip* wep, player* ply)
{
    switch(wParam) {
        case VK_SPACE:
            break;
    }
}

void inputs::keyUp()
{

}

void inputs::mouseWhip(whip* wep, player* ply, double x, double y,sounds *sds)
{
    prev_Mx = x;
    prev_My = y;

    switch(wParam) {
        case MK_LBUTTON:
            sds->playSound("sounds/whip.mp3");
            wep->wPos.x = ply->pPos.x;
            wep->wPos.y = ((ply->pPos.y - 0.15) * 0.67) - 0.1;
            wep->wPos.z = -2;
            if (ply->playerDir == 'L') {
                wep->wEnd.x = -3.0;
                wep->wEnd.y = 1.1;
            }
            else if (ply->playerDir == 'R') {
                wep->wEnd.x = 3.0;
                wep->wEnd.y = 1.1;
            }

            wep->t = 0;
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
}

void inputs::keyPowerUp(powerups* pow, float speed)
{
    if (keys[VK_LEFT] || keys[0x41]) {
        pow->powPos.x += speed;
    }

    if (keys[VK_RIGHT] || keys[0x44]) {
        pow->powPos.x -= speed;
    }
}

