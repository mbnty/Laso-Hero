#ifndef UI_H
#define UI_H

#include <textureLoader.h>
#include <player.h>


class ui
{
    public:
        ui();
        virtual ~ui();

        void drawSquare(float, float, int);
        void initUi(char*, int);

        float xMax,xMin, yMax,yMin;

        GLuint uTex[100];
        textureLoader *uLoad = new textureLoader();

    protected:

    private:
};

#endif // UI_H
