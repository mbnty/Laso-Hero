#ifndef FONTS_H
#define FONTS_H

#include <commons.h>
#include <textureLoader.h>
#include <string.h>

typedef struct{
    char letter;
    float offset;
    vec3 fontSize;
}charset;

class fonts
{
    public:
        fonts();
        virtual ~fonts();

        void initFonts(char *);
        void buildFonts(int);
        void drawFonts(int, float);

        float xMin, xMax, yMin, yMax;
        charset C[1024];

        vec3 Rotate;
        vec3 pos;
        float zoom;

        int cCnt;
        bool run;

        GLuint tex;
        textureLoader *tLoad = new textureLoader();

    protected:

    private:
};

#endif // FONTS_H
