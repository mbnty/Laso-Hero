#ifndef CHECKCOLLISION_H
#define CHECKCOLLISION_H
#include <commons.h>

#include <player.h>
#include <enemy.h>
#include <platform.h>
#include <whip.h>

class checkCollision
{
    public:
        checkCollision();
        virtual ~checkCollision();

        bool isLinearCollision(float, float);
        bool isRadialCollision(float, float, float, float, float, float);
        bool isSphereCollision(vec3 x, vec3 y);
        bool isQuadCollisionPlatform(player*, platform*);
<<<<<<< HEAD
        bool isQuadCollisionEnemy(player*, enemy);
=======
        bool isQuadCollisionEnemy(player*, enemy*);
        bool isQuadCollisionWhip(whip*, enemy*);
>>>>>>> 16a6b5fd4a10ad38dbaf556d2573ef1cc85ee13d


    protected:

    private:
};

#endif // CHECKCOLLISION_H
