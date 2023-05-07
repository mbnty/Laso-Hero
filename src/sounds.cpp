#include "sounds.h"

sounds::sounds()
{
    //ctor
}

sounds::~sounds()
{
    //dtor
}

void sounds::playMusic(char* file)
{
    engine->play2D(file,true);    //play file and true to run on a loop
}

void sounds::playSound(char* file)
{
    if (!engine->isCurrentlyPlaying(file))
    {
        engine->play2D(file, false, false);
    }
}

void sounds::pauseSound(char* file)
{
    engine->play2D(file, true, false);
}

int sounds::initSound()
{
    if (!engine)
    {
        cout << "The Sound Engine did not start" << endl;
        return 0;
    }
    return 1;
}
