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
        vec3 wEnd;

    protected:

    private:
};

#endif // WHIP_H
