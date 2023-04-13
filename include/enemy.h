#ifndef ENEMY_H
#define ENEMY_H
#include<string>
#include<GL/glut.h>
#include<textureLoader.h>
#include<positions.h>
#include<time.h>

class enemy
{
    public:
        enemy();
        virtual ~enemy();

        void drawEnemy();
        void placeEnemy(pos3);
        void initEnemy(GLuint, int, int);
        void enemySkin(char *);

        enum acts{IDLE, WALKR, WALKL, JUMP, ATTACK, DIE};
        void actions();
        acts movement;

        int hFrames;
        int vFrames;

        float xMax, yMax, xMin, yMin;
        pos3 enemyPosition;
        pos2 enemySize;
        pos2 enemySpeed;

        pos3 enemyRotation;

        GLuint tex;
        textureLoader *tLoad = new textureLoader();

        clock_t currTime;
    protected:

    private:
};

#endif // ENEMY_H
