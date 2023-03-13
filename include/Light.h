#ifndef LIGHT_H
#define LIGHT_H

#include<GL/gl.h>
#include<scene.h>


class Light:public scene
{
    public:
        Light(GLenum);
        virtual ~Light();

        GLfloat light_ambient[4]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat light_diffuse[4]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat light_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat light_position[4] = { 2.0f, 5.0f, 5.0f, 0.0f };

        GLfloat mat_ambient[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
        GLfloat mat_diffuse[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat mat_specular[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat high_shininess[1] = { 100.0f };

        void setLight(GLenum);

    protected:

    private:
};

#endif // LIGHT_H
