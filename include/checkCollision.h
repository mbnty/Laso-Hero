#ifndef CHECKCOLLISION_H
#define CHECKCOLLISION_H
#include <commons.h>

#include <player.h>
#include <enemy.h>
#include <platform.h>
#include <whip.h>
#include <powerups.h>

class checkCollision
{
    public:
        checkCollision();
        virtual ~checkCollision();

        bool isLinearCollision(float, float);
        bool isRadialCollision(float, float, float, float, float, float);
        bool isSphereCollision(vec3 x, vec3 y);
        bool isQuadCollisionPlatform(player*, platform*);
        bool isQuadCollisionEnemy(player*, enemy);
        bool isQuadCollisionWhip(whip*, enemy);
        bool isQuadCollisionPowerUp(player*, powerups*);
        bool QuadEnemytoPlayer(enemy, player*);


    protected:

    private:
};

#endif // CHECKCOLLISION_H
