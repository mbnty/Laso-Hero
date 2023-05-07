#include "particles.h"

particles::particles()
{
    //ctor
}

particles::~particles()
{
    //dtor
}

void particles::drawParticles()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPushMatrix();
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_DROPS; i++) {
        if (i % 3 == 0) {
            glColor4f(0.99, 0.98, 0.83, 1.0);
        }
        else {
            glColor4f(1.0, 0.93, 0.36, 0.5);
        }
        if (drops[i].alive) {
            glVertex3f(drops[i].pos.x, drops[i].pos.y, -9.5);
        }
    }
    glEnd();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
}

void particles::updateParticles()
{
    for (int i = 0; i < MAX_DROPS; i++) {
        if (drops[i].alive) {               // Use time control
            drops[i].pos.x += 0.03;
            drops[i].pos.y -= 0.005;
            drops[i].alpha -= 0.007;

            if (drops[i].alpha <= 0) {
                drops[i].alive = false;
                numDrops--;
            }
        }
    }
}

void particles::generateParticles(float x, float y)
{
    int newDrops = rand()%60 + 1;

    // To make sure not exceed array
    if (numDrops + newDrops > MAX_DROPS)
        newDrops = MAX_DROPS - numDrops;

    numDrops += newDrops;
    for (int i = 0; i < MAX_DROPS; i++) {
        if (drops[i].alive == false) {
            drops[i].alive = true;
            drops[i].pos.x = drand48() - 8;
            drops[i].pos.y = drand48() * 11 - 5;
            drops[i].alpha = (float)(rand() % 100) / 10.0;
            newDrops--;
        }
        if (newDrops == 0)
            break;
    }

    if (numDrops >= MAX_DROPS) {
        numDrops = 0;
    }
}
