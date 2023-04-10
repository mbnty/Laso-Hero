#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <model.h>
#include <player.h>
#include <title.h>

class inputs
{
    public:
        inputs();
        virtual ~inputs();

        void keyModel(model*);

        void keyPlayer();
        void mousePlayer();

        void keyEnv();
        void keyPlayer(player*);
        int keyTitle(title*);

        void keyUp();
        void mouseMove(double, double);

        void updateWParam(WPARAM);

    protected:

    private:
        WPARAM wParam;

        double prev_Mx;
        double prev_My;
};

#endif // INPUTS_H
