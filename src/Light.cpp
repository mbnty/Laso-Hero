#include "Light.h"

Light::Light(GLenum light)
{
    //ctor
}

Light::~Light()
{
    //dtor
}

void Light::setLight(GLenum Lit)
{
    glLightfv(Lit, GL_AMBIENT,  light_ambient);
    glLightfv(Lit, GL_DIFFUSE,  light_diffuse);
    glLightfv(Lit, GL_SPECULAR, light_specular);
    glLightfv(Lit, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

