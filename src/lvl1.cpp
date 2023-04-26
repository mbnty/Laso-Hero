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
    pl1->drawPlatform();
    sp1->drawPlatform();
    pl2->drawPlatform();
    pl3->drawPlatform();
    sp2->drawPlatform();
    pl4->drawPlatform();
    pl5->drawPlatform();
    sp2->drawPlatform();

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

    pl1->place(0,0,5,1);
    sp1->place(1,-1.4,1,0.5);
    pl2->place(6,0,3,1);
    pl3->place(10,0,2,1);
    sp2->place(11,-1.4,1,0.5);
    pl4->place(11.5,0,2,1);
    pl5->place(18,0,5,1);
    sp2->place(18,-1.4,2,0.5);
}

