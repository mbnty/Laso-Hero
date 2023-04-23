#ifndef COMMONS_H
#define COMMONS_H
#define GRVITY 9.81
#define PI 3.14159

#include <math.h>
#include <GL/gl.h>
#include <iostream>
#include <time.h>

using namespace std;

typedef struct
{
    float x;
    float y;
    float z;
}vec3;

typedef struct
{
    float x;
    float y;
}vec2;

class commons
{
    public:
        commons();
        virtual ~commons();

    protected:

    private:
};
#endif // COMMONS_H
