#ifndef CHECKCOLLISION_H
#define CHECKCOLLISION_H
#include <commons.h>

#include <player.h>
#include <platform.h>

class checkCollision
{
    public:
        checkCollision();
        virtual ~checkCollision();

        bool isLinearCollision(float, float);
        bool isRadialCollision(float, float, float, float, float, float);
        bool isSphereCollision(vec3 x, vec3 y);
        bool isQuadCollisionPlatform(player*, platform*);

    protected:

    private:
};

#endif // CHECKCOLLISION_H
