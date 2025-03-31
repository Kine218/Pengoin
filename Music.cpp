#include "Music.h"
#include "Common_Function.h"
Mix_Music* backgroundMusic = nullptr;
Mix_Chunk* jumpsound = nullptr;
Mix_Chunk* clicksound=nullptr;
Mix_Chunk* endsound=nullptr;
void Music::MusicInit()
{
    backgroundMusic = Mix_LoadMUS("music/m2.mp3");
    clicksound=Mix_LoadWAV("music/click.wav");
    jumpsound=Mix_LoadWAV("music/jump.wav");
    endsound=Mix_LoadWAV("music/gameover.wav");
    if (!jumpsound)
    {
    std::cout << "Lỗi tải hiệu ứng: " << Mix_GetError() << std::endl;
    }
    if (!backgroundMusic)
    {
    std::cout << "Lỗi tải âm thanh nền: " << Mix_GetError() << std::endl;
    }
    if (!clicksound)
    {
    std::cout << "Lỗi tải hiệu ứng: " << Mix_GetError() << std::endl;
    }
}
void Music::JumpSound()
{
   Mix_VolumeChunk(jumpsound, jumpsound_volumn);
   Mix_PlayChannel(-1, jumpsound, 0);
}
void Music::ClickSound()
{
   Mix_VolumeChunk(clicksound, clicksound_volumn);
   Mix_PlayChannel(-1, clicksound, 0);
}
void Music::GameOver()
{
   Mix_VolumeChunk(endsound, jumpsound_volumn);
   Mix_PlayChannel(-1, endsound, 0);
}

void Music::FreeMusic()
{
    Mix_FreeMusic(backgroundMusic);
}
void Music::PlayBackgroundMusic()
{   Mix_VolumeMusic(backgroundmusic_volumn);
       if (backgroundMusic)
    {
        Mix_PlayMusic(backgroundMusic, -1); // Lặp vô hạn
    }
}
void Music::backgroundmusic_change(int slider)
{
    backgroundmusic_volumn=float(slider-480)*0.2;
    Mix_VolumeMusic(backgroundmusic_volumn);
}
void Music::soundeffect_change(int slider)
{
    jumpsound_volumn =float(slider-480)*0.1;
    clicksound_volumn=float(slider-480)*0.05;
    Mix_VolumeChunk(jumpsound, jumpsound_volumn);
    Mix_VolumeChunk(clicksound, clicksound_volumn);
}
std::string Music::getBackvolumn(int slider)
{
    std::string x=" ";
    float alter=float(slider);
    alter=(alter-480)/160*100;
    int alterr=int(alter);
    while (alterr>0)
    {
        x=char(alterr%10+'0')+x;
        alterr/=10;
    }
    if (x==" ") return "0 ";
    return x;
}

std::string Music::getEffectvolumn(int slider)
{
    std::string x=" ";
    float alter=float(slider);
    alter=(alter-480)/160*100;
    int alterr=int(alter);
    while (alterr>0)
    {
        x=char(alterr%10+'0')+x;
        alterr/=10;
    }
    if (x==" ") return "0 ";
    return x;
}

