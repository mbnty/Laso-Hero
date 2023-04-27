#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <model.h>
#include <player.h>
#include <title.h>
#include <whip.h>
#include <bullet.h>
#include <parallax.h>
#include <lvl1.h>
#include <enemy.h>
#include <powerups.h>

class inputs
{
    public:
        inputs();
        virtual ~inputs();

        bool keys[256];

        void getRealMouse(int, int);

        void keyModel(model*);

        void keyPlayer();
        void mousePlayer();

        void keyEnv(parallax &, float);
        void keyPlayer(player*);
        int keyTitle(title*);
        void keyWhip(whip*, player*);
        int keyPause();
        void keyEnemy(enemy&);

        void keyUp();
        void mouseWhip(whip*, player*, double, double);
        void mouseMove(double, double);

        void keyBullet(bullet*, player*);

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
