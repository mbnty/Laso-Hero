#ifndef PLATFORM_H
#define PLATFORM_H

#include <commons.h>
#include <textureLoader.h>

class platform
{
    public:
        platform();
        virtual ~platform();

        vec3 scaleSize;
        vec3 verts[4];
        vec3 pos;
        float xMax, yMax, xMin, yMin;
        int hFrames; //horizontal frames
        int vFrames; //vertical frames

        void drawPlatform(float,float,float,float);
        void initPlatform(char *, int, int);

        GLuint tex;
        textureLoader *tLoad = new textureLoader();

    protected:

    private:
};

#endif // PLATFORM_H
