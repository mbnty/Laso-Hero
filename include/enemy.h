#ifndef ENEMY_H
#define ENEMY_H
#include<string>
#include<GL/glut.h>
#include<textureLoader.h>
#include<positions.h>
#include<player.h>
#include<sounds.h>
#include<platform.h>
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
        void enemySkinMulti(char *, GLuint &);
        void enemyAIManager(player*);
        bool enemyPlayerCollisionAttack(player*);
        bool enemyMoveCollisionLinear(player*);
        bool checkPlayerHit(player*);
        bool enemyPlatformCollision(platform*);


        void setAsSpear();

        enum acts{IDLE, WALKR, WALKL, JUMP, FALL, ATTACK, HURT, DIE};
        void actions();
        acts movement;

        char enDir; //direction enemy is facing

        int hFrames;
        int hFramesInd[10];

        int vFrames;
        int vFramesInd[10];

        float xMax, yMax, xMin, yMin;
        float enemyOffsetY;
        float groundValue;
        pos3 enemyPosition;
        pos3 initialPosition;
        pos2 enemySize;
        pos3 enemyColor;
        pos2 enemySpeed;

        pos3 enemyRotation;

        int indexTexture;
        GLuint tex;
        GLuint texInd[10];
        textureLoader *tLoad = new textureLoader();

        bool isHit;
        bool isDead;
        bool isIdle;
        bool isAttack;
        bool isSpawn;
        bool isJump;
        int enHP;

        clock_t currTime;
        clock_t attackTimer;
        clock_t jumpTimer;
        clock_t DeathTimer;

        sounds *snd = new sounds();

        float velocity;
        float theta;
        float t;
        float jumpSpeed;
        float airSpeed;

    protected:

    private:
};

#endif // ENEMY_H
