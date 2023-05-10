#include "parallax.h"

//constructor sets positions of xMin, xMax, yMin, yMax
parallax::parallax()
{
    xMax = 1.0;
    xMin = 0.0;
    yMax = 0.0;
    yMin = 1.0;

    startTime = clock();
}

parallax::~parallax()
{
    //dtor
}

void parallax::initPopUp(char* fileName)
{
    bLoad->loadTexture(fileName, bTex);
}

void parallax::resetParallax()
{
    xMax = 1.0;
    xMin = 0.0;
    yMax = 0.0;
    yMin = 1.0;

    startTime = clock();
}

void parallax::drawPopUp(float width, float height)
{
    glColor3f(1.0,1.0,1.0);
    bLoad->binder(bTex);

    glScalef(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMin);
        glVertex3f(-1.0 * width/height, -1.0, 0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(width/height, -1.0, 0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(width/height, 1.0, 0);

        glTexCoord2f(xMin, yMax);
        glVertex3f(-1.0 * width/height, 1.0, 0);
    glEnd();
}


//function draws a square and binds the texture to it
void parallax::drawSquare(float width, float height)
{
    bLoad->binder(bTex);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glTexCoord2f(xMin,yMin); glVertex3f(-1*width/height,-1.0,-10.0);
    glTexCoord2f(xMax,yMin); glVertex3f(width/height,-1.0,-10.0);
    glTexCoord2f(xMax,yMax); glVertex3f(width/height,1.0,-10.0);
    glTexCoord2f(xMin,yMax); glVertex3f(-1*width/height,1.0,-10.0);
    glEnd();
}

//function initializes the parallax by using the texture loader to load a file to the texture handler
void parallax::initParallax(char *fileName)
{
    glEnable(GL_COLOR_MATERIAL);
    bLoad->loadTexture(fileName, bTex);
}

//function scrolls through image depending on direction and speed
void parallax::scroll(bool scrl, string direction, float speed)
{
    if(scrl)
    {
        if (clock()-startTime > 15)
        {
            if (direction == "x")
            {
                xMin += speed;
                xMax += speed;
            }
            else if (direction == "-x")
            {
                xMin -= speed;
                xMax -= speed;
            }
            else if (direction == "y")
            {
                yMin -= speed;
                yMax -= speed;
            }
            else
            {
                yMin += speed;
                yMax += speed;
            }

            startTime = clock();
        }
    }
}
