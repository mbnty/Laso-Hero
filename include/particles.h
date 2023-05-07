#ifndef PARTICLES_H
#define PARTICLES_H

#include <commons.h>

class particles
{
    public:
        particles();
        virtual ~particles();

        typedef struct {
            bool alive;
            vec3 pos;
            vec3 dir;
            float mass;
            float alpha;

            // Optional data (delete if you don't use it)
            float radius;
            float expRadius;
            vec3 velocity;
        }particle;

        particle drops[MAX_DROPS];

        void drawParticles();
        void updateParticles();
        void generateParticles(float, float);

        float drand48() { return (rand()%100 + 1) / 100.0; }
        int numDrops = 0;

    protected:

    private:
};

#endif // PARTICLES_H
