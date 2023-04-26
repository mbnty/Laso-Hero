#ifndef POWERUPS_H
#define POWERUPS_H

#include <textureLoader.h>
#include <enemy.h>
#include <commons.h>

class powerups
{
    public:
        powerups();
        virtual ~powerups();
        void initPowerUp(GLuint);
        void drawSquare();
        void powTexture(char*);
        int dropPowerUp(pos3);

        enum acts{IDLE, MOVEL, MOVER};
        acts act;
        void actions();

        float xMax, xMin, yMax, yMin;

        vec3 powPos;
        vec3 scaleSize;

        int isHit;

        GLuint powTex;
        textureLoader *powLoad = new textureLoader();

    protected:

    private:
};

#endif // POWERUPS_H
