#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <iostream>
#include <SOIL.h>
#include <GL/gl.h>

using namespace std;

class textureLoader
{
    public:
        textureLoader();                     //constructor
        virtual ~textureLoader();            //destructor

        void loadTexture(char *, GLuint &);  //to load images
        void binder(GLuint);                 //to bind images

        unsigned char *image;                //to hold image data
        int width, height;                   //image width and height

    protected:

    private:
};

#endif // TEXTURELOADER_H
