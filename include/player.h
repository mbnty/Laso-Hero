#ifndef PLAYER_H
#define PLAYER_H

#include <textureLoader.h>
#include <commons.h>

class player
{
    public:
        player();
        virtual ~player();

        vec3 scaleSize;
        vec3 verts[4];

        enum acts{IDLE, WALKR, WALKL, JUMP, ATTACK, DIE};

        float runSpeed;
        float jumpSpeed;
        acts actionTrigger;

        char playerDir;  //to find out where player is heading

        void drawPlayer();
        void playerInit(char *, int, int);
        void actions(acts);

        int hFrames; //horizontal frames
        int vFrames; //vertical frames

        float xMax, yMax, xMin, yMin;
        vec3 pPos;  //player position

        GLuint tex;
        textureLoader *tLoad = new textureLoader();

    protected:

    private:
};

#endif // PLAYER_H
