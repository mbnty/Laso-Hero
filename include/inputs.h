#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <model.h>
#include <player.h>
#include <title.h>
#include <whip.h>
#include <parallax.h>
#include <lvl1.h>
#include <enemy.h>
#include <powerups.h>
#include <sounds.h>
#include <particles.h>

class inputs
{
    public:
        inputs();
        virtual ~inputs();

        bool keys[256] = { false };

        void getRealMouse(int, int);

        void keyModel(model*);

        void keyPlayer();
        void mousePlayer();

        void keyEnv(parallax &, float);
        void keyPlayer(player*, sounds*, particles*);
        int keyTitle(title*,sounds*);
        int keyQuit(title*,sounds*);
        void keyWhip(whip*, player*);
        int keyPause();
        void keyEnemy(enemy&);

        void keyUp();
        void mouseWhip(whip*, player*, double, double,sounds*);
        void mouseMove(double, double);

        void updateWParam(WPARAM);

        void keyEnvL1(platform*, float);

        void keyPowerUp(powerups*, float);

    protected:

    private:
        WPARAM wParam;

        double prev_Mx;
        double prev_My;

        GLdouble realX;
        GLdouble realY;
        GLdouble realZ;
};

#endif // INPUTS_H
