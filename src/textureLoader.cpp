#include "textureLoader.h"

textureLoader::textureLoader()
{
    //ctor
}

textureLoader::~textureLoader()
{
    //dtor
}

//loading function for textures takes file name and texture ID through the use of SOIL
void textureLoader::loadTexture(char* fileName, GLuint &textureID)
{
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    image = SOIL_load_image(fileName,&width,&height,0,SOIL_LOAD_RGBA);  //let soil load image
    if(!image){cout << "No image found";}                               //check for image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); //load image into bucket

    SOIL_free_image_data(image); //clear out image data

    //wrap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //filter
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

//function to bind texture to object
void textureLoader::binder(GLuint textureID)
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}
