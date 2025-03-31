#ifndef MUSIC_H
#define MUSIC_H
#include "Common_Function.h"

class Music
{
    public:
       void PlayBackgroundMusic ();
       void JumpSound();
       void ClickSound();
       void GameOver();
       static void FreeMusic();
       static void MusicInit();
     void backgroundmusic_change(int slider);
     void soundeffect_change(int slider);

       std::string getBackvolumn(int slider);
       std::string getEffectvolumn(int slider);
    private:
     float clicksound_volumn=4;
     float backgroundmusic_volumn=16;
     float jumpsound_volumn=8;
};

#endif // MUSIC_H
