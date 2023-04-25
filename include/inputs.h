#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <model.h>
#include <player.h>
#include <title.h>
#include <whip.h>
#include <parallax.h>
#include <lvl1.h>
#include<enemy.h>

class inputs
{
    public:
        inputs();
        virtual ~inputs();

        void getRealMouse(int, int);

        void keyModel(model*);

        void keyPlayer();
        void mousePlayer();

        void keyEnv(parallax &, float);
        void keyPlayer(player*);
        int keyTitle(title*);
        void keyWhip(whip*, player*);
<<<<<<< HEAD
        int keyPause(parallax&);
=======
        void keyEnemy(enemy *);
>>>>>>> 7f8d252fa971be82b5ed5e5cfc5d0cfa42e33352

        void keyUp();
        void mouseWhip(whip*, player*, double, double);
        void mouseMove(double, double);

        void updateWParam(WPARAM);

        void keyEnvL1(lvl1 *, float);

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
