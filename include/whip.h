#ifndef WHIP_H
#define WHIP_H

#include <commons.h>
#include <textureLoader.h>

class whip
{
    public:
        whip();
        virtual ~whip();

        void initWhip(char*);
        void drawWhip();
        vec3 wPos;
        vec3 wEnd;
        bool run;

        float t;

    protected:

    private:
        GLuint tex;
        textureLoader *tLoad = new textureLoader();
};

#endif // WHIP_H
