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
    if((fabs(x1-x2)) < 0.1) return true;
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

bool checkCollision::isQuadCollisionPlatform(player* p1, platform* pl)
{
    // collision x-axis
    bool collisionX = p1->pPos.x + 0.5 >= pl->pos.x &&
        pl->pos.x + (0.25 * pl->scaleSize.x) >= p1->pPos.x;
    // collision y-axis
    bool collisionY = p1->pPos.y + 0.5 >= pl->pos.y &&
        pl->pos.y + (0.25 * pl->scaleSize.y) >= p1->pPos.y;
    // collision only if on both axes
    return collisionX && collisionY;
}
