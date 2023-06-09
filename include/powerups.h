#ifndef POWERUPS_H
#define POWERUPS_H

#include <commons.h>
#include <textureLoader.h>
#include <positions.h>

class powerups
{
    public:
        powerups();
        virtual ~powerups();
        void initPowerUp(GLuint);
        void drawSquare();
        void powTexture(char*);
        void dropBullet(pos3);
        void dropHealth(pos3);

        void resetPowerUp();

        enum acts{INIT, IDLE, DROP, PICKUP, MOVEL, MOVER};
        acts act;
        void actions();

        float xMax, xMin, yMax, yMin;
        vec3 powPos;
        vec3 scaleSize;

        int isHit;
        bool isDropped;

        GLuint powTex;
        textureLoader *powLoad = new textureLoader();

    protected:

    private:
};

#endif // POWERUPS_H
