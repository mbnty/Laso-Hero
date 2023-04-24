#ifndef LVL1_H
#define LVL1_H

#include <commons.h>
#include <platform.h>

class lvl1
{
    public:
        lvl1();
        virtual ~lvl1();

        void drawLvl1();
        void initLvl1();

        float levelPosX;

        platform *pl1 = new platform();
        platform *pl2 = new platform();
        platform *pl3 = new platform();
        platform *sp1 = new platform();

    protected:

    private:
};

#endif // LVL1_H
