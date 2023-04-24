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
    pl1->drawPlatform(0,0,5,1);
    sp1->drawPlatform(1,-1.4,1,0.5);
    pl2->drawPlatform(6,0,3,1);
    pl3->drawPlatform(10,0,2,1);
    sp2->drawPlatform(11,-1.4,1,0.5);
    pl4->drawPlatform(11.5,0,2,1);
    pl5->drawPlatform(18,0,5,1);
    sp2->drawPlatform(18,-1.4,2,0.5);

    glPopMatrix();
}

void lvl1::initLvl1()
{
    pl1->initPlatform("images/platform1.png",1,1);
    pl2->initPlatform("images/platform1.png",1,1);
    pl3->initPlatform("images/platform1.png",1,1);
    pl4->initPlatform("images/platform1.png",1,1);
    pl5->initPlatform("images/platform1.png",1,1);

    sp1->initPlatform("images/spikes.png",1,1);
    sp2->initPlatform("images/spikes.png",1,1);
    sp3->initPlatform("images/spikes.png",1,1);
}

