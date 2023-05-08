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
    glPointSize(dotSize);
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_DROPS; i++) {
        if (drops[i].alive) {
            glColor4f(drops[i].color.x, drops[i].color.y, drops[i].color.z, 0.8);
            glVertex3f(drops[i].pos.x, drops[i].pos.y, drops[i].pos.z);
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
            drops[i].pos.z = -9.5;
            if (i % 3 == 0) {
                drops[i].color.x = 0.99;
                drops[i].color.y = 0.98;
                drops[i].color.z = 0.83;
            }
            else {
                drops[i].color.x = 1.0;
                drops[i].color.y = 0.93;
                drops[i].color.z = 0.36;
            }
            drops[i].alpha = (float)(rand() % 100) / 10.0;
            dotSize = 2;
            newDrops--;
        }
        if (newDrops == 0)
            break;
    }

    if (numDrops >= MAX_DROPS) {
        numDrops = 0;
    }
}

void particles::genJumpParticles(float x, float y)
{
    int newDrops = 300;
    for (int i = numDrops; i < numDrops + newDrops; i++) {
        drops[i].alive = true;
        drops[i].pos.x = x;
        drops[i].pos.y = y - 0.6;
        drops[i].pos.z = -3;
        if (i % 2 == 0) {
            drops[i].color.x = 0.45;
            drops[i].color.y = 0.24;
            drops[i].color.z = 0.05;
        }
        else {
            drops[i].color.x = 1.0;
            drops[i].color.y = 0.93;
            drops[i].color.z = 0.36;
        }
        drops[i].alpha = (float)(rand() % 100) / 10.0;
        dotSize = 3;
    }
    numDrops += newDrops;
}

void particles::updateJumpParticles()
{
    for (int i = 0; i < MAX_DROPS; i++) {
        if (drops[i].alive) {
            drops[i].pos.x += sin(rand() % 360) * 0.015;
            drops[i].pos.y += cos((rand() % 90) * PI/180) * 0.003;
            drops[i].alpha -= 0.05;

            if (drops[i].alpha <= 0) {
                drops[i].alive = false;
                numDrops--;
            }
        }
    }
}

void particles::resetParticles()
{
    for (int i = 0; i < MAX_DROPS; i++) {
        if (drops[i].alive == true) {
            drops[i].alive = false;
        }
    }
    numDrops = 0;
}
