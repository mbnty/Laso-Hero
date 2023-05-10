#ifndef BULLET_H
#define BULLET_H

#include <textureLoader.h>
#include <commons.h>

class bullet
{
    public:
        bullet();
        virtual ~bullet();

        void drawBullet();
        void placeBullet(vec3);
        void initBullet(GLuint);
        void projTexture(char *);

        void resetBullet();

        enum acts{IDLE, MOVEL, MOVER};
        acts act;
        void actions();

        vec3 bPos;
        GLuint tex;

    protected:

    private:
        float xMax, xMin, yMax, yMin;       // Texture coords
        clock_t start;

        textureLoader *tLoad = new textureLoader();
};

#endif // BULLET_H
