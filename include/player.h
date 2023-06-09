#ifndef PLAYER_H
#define PLAYER_H

#include <textureLoader.h>
#include <commons.h>
#include <sounds.h>
#include <particles.h>

class player
{
    public:
        player();
        virtual ~player();

        vec3 scaleSize;
        vec3 pColor;
        vec3 verts[4];

        enum acts{IDLE, WALKR, WALKL, JUMP, ATTACK, HURT};

        float runSpeed;
        float jumpSpeed;
        float theta, velocity, t;
        acts actionTrigger;

        int health, ammo;
        int MAX_HEALTH, MAX_AMMO;

        char playerDir;  //to find out where player is heading

        void drawPlayer();
        void playerInit(char *, int, int);
        void actions(acts, sounds*, particles*);

        void resetPlayer();

        int hFrames; //horizontal frames
        int vFrames; //vertical frames

        float xMax, yMax, xMin, yMin;
        vec3 pPos;  //player position

        GLuint tex;
        textureLoader *tLoad = new textureLoader();

        clock_t start, frame, damage;

        float groundValue;

        bool onPlat;
        bool isIdle;
        bool isJump;

    protected:

    private:
};

#endif // PLAYER_H
