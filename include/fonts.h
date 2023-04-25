#ifndef FONTS_H
#define FONTS_H

#include <commons.h>
#include <textureLoader.h>
#include <string.h>

typedef struct{
    char letter;
    float xMin, xMax, yMin, yMax;
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
        void drawFonts(float, float, float, int);
        charset C[1024];

        vec3 Rotate;
        vec3 pos;
        float zoom;

        int cCnt;

        GLuint fTex;
        textureLoader *fLoad = new textureLoader();

    protected:

    private:
};

#endif // FONTS_H
