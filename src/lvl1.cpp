#include "lvl1.h"

lvl1::lvl1()
{
    //ctor

}

lvl1::~lvl1()
{
    //dtor
}

void lvl1::drawLvl1()
{
    glTranslatef(levelPosX,0,0);
    glPushMatrix();
    pl1->drawPlatform(1,0,4,1);
    sp1->drawPlatform(1,-1.4,0.5,0.5);
    pl2->drawPlatform(5,0,3,1);
    pl3->drawPlatform(8,0,1,1);

    glPopMatrix();
}

void lvl1::initLvl1()
{
    pl1->initPlatform("images/platform1.png",1,1);
    pl2->initPlatform("images/platform1.png",1,1);
    pl3->initPlatform("images/platform1.png",1,1);
    sp1->initPlatform("images/spikes.png",1,1);
}
