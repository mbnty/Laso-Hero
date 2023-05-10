#ifndef SOUNDS_H
#define SOUNDS_H

#include <commons.h>

class sounds
{
    public:
        sounds();
        virtual ~sounds();

        ISoundEngine *engine = createIrrKlangDevice();

        void playMusic(char*);
        void playSound(char*);
        void pauseSound(char*);  //pause the sound when window minimized
        int initSound();       //initialization of sounds
        void changeMusic(char*,char*);

    protected:

    private:
};

#endif // SOUNDS_H
