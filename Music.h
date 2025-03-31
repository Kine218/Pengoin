#ifndef MUSIC_H
#define MUSIC_H
#include "Common_Function.h"

class Music
{
    public:
       void PlayBackgroundMusic ();
       void JumpSound();
       void ClickSound();
       static void FreeMusic();
       static void MusicInit();

    private:
     int clicksound_volumn=4;
     int backgroundmusic_volumn=16;
     int jumpsound_volumn=8;
};

#endif // MUSIC_H
