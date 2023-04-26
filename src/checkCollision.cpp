#include "checkCollision.h"

// Hi

checkCollision::checkCollision()
{
    //ctor
}

checkCollision::~checkCollision()
{
    //dtor
}

bool checkCollision::isLinearCollision(float x1, float x2)
{
    if((fabs(x1-x2)) < 0.05) return true;
    else return false;
}

bool checkCollision::isRadialCollision(float x1, float x2, float y1, float y2, float r1, float r2)
{
    if(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) < (r1 + r2)) return true;
    else return false;
}

bool checkCollision::isSphereCollision(vec3 x, vec3 y)
{

}

bool checkCollision::isQuadCollisionPlatform(player* ply, platform* plat)
{
    // collision x-axis
    bool collisionX = ply->pPos.x + 0.5 >= plat->pos.x - (0.25 * plat->scaleSize.x) &&
        plat->pos.x + (0.25 * plat->scaleSize.x) >= ply->pPos.x - 0.5;
    // collision y-axis
    bool collisionY = ply->pPos.y + 0.5 >= plat->pos.y - (0.25 * plat->scaleSize.y) &&
        plat->pos.y + (0.25 * plat->scaleSize.y) >= ply->pPos.y - 0.5;

    return collisionX && collisionY;
}
