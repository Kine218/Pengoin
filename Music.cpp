#include "Music.h"
#include "Common_Function.h"
Mix_Music* backgroundMusic = nullptr;
Mix_Chunk* jumpsound = nullptr;
Mix_Chunk* clicksound=nullptr;
void Music::MusicInit()
{
    backgroundMusic = Mix_LoadMUS("music/m2.mp3");
    clicksound=Mix_LoadWAV("music/click.wav");
    jumpsound=Mix_LoadWAV("music/jump.wav");
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



