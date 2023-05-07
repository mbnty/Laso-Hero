#ifndef PARALLAX_H
#define PARALLAX_H

#include <textureLoader.h>
#include <time.h>

class parallax
{
    public:
        parallax();              //constructor
        virtual ~parallax();     //destructor

        void drawSquare(float, float);      //used to draw the square to hold the background
        void initParallax(char *);         //initialization
        void scroll(bool, string, float);   //used to scroll the image
        void initPopUp(char*);
        void drawPopUp(float, float);

        float xMax,xMin, yMax,yMin;         //used hold the points of the image

        GLuint bTex;                                 //texture handler
        textureLoader *bLoad = new textureLoader();  //create instance of texture loader

        clock_t startTime;

    protected:

    private:
};

#endif // PARALLAX_H
