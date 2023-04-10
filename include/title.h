#ifndef TITLE_H
#define TITLE_H

#include <textureLoader.h>

class title
{
    public:
        title();
        virtual ~title();

        void drawTitle(float, float);
        void drawSquare(float, float, int);
        void initTitle(char*);
        void initOption(char*, int);

        float xMax, xMin, yMax, yMin;
        int selection;

        textureLoader *bTex = new textureLoader();
        GLuint tex[4];

    protected:

    private:
};

#endif // TITLE_H