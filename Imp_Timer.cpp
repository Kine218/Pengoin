#include "Imp_Timer.h"
#include "Common_Function.h"
Imp_Timer::Imp_Timer()
{
    paused_tick=0;
    start_tick=0;
    is_paused_=false;
    is_started_=false;
}

Imp_Timer::~Imp_Timer()
{

}
void Imp_Timer::start()
{
   is_started_=true;
   is_paused_=false;
   start_tick=SDL_GetTicks();
}

void Imp_Timer::stop()
{
   is_started_=false;
   is_paused_=false;
}

void Imp_Timer::paused()
{  if (is_started_==true&&is_paused_==false)
   {is_paused_=true;
   paused_tick=SDL_GetTicks()-start_tick;
   }
}

void Imp_Timer::unpaused()
{
   if (is_paused_==true)
   {

       is_paused_=false;
       start_tick=SDL_GetTicks()-paused_tick;
       paused_tick=0;
   }
}

int Imp_Timer::get_ticks()
{
   if (is_started_)
   {
       if (is_paused_)
        return paused_tick;
       else
        return SDL_GetTicks()-start_tick;
   }
   return 0;
}

bool Imp_Timer::is_paused()
{
   return is_paused_;
}

bool Imp_Timer::is_started()
{
   return is_started_;
}
