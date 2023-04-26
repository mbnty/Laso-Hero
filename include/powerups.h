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

        float xMax, xMin, yMax, yMin;

        vec3 powPos;

        bool isHit;

        GLuint powTex;
        textureLoader *powLoad = new textureLoader();

    protected:

    private:
};

#endif // POWERUPS_H
