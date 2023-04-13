#ifndef WHIP_H
#define WHIP_H

#include <commons.h>

class whip
{
    public:
        whip();
        virtual ~whip();

        void drawWhip(float);
        vec3 wPos;
        GLfloat x;
        GLfloat y;

    protected:

    private:
};

#endif // WHIP_H
