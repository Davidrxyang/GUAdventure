#include "timer.h"

Timer::Timer()
{
    start_ticks = 0;
    paused_ticks = 0;
    paused = false;
    started = false;
} // default constructor

void Timer::start()
{
    started = true;
    paused = false;
    start_ticks = SDL_GetTicks();
    paused_ticks = 0;
} // Timer::start

void Timer::stop()
{
    started = false;
    paused = false;
    start_ticks = 0;
    paused_ticks = 0; // reset the clock, stop it
} // Timer::stop

void Timer::pause()
{
    if (started && !paused)
    {
        paused = true;
        paused_ticks = SDL_GetTicks() - start_ticks;
        start_ticks = 0;
    } // if - if the clock is not started or already paused, do nothing
} // Timer::paused

void Timer::unpause()
{
    if (started && paused)
    {
        paused = false;
        start_ticks = SDL_GetTicks() - paused_ticks;
        paused_ticks = 0;
    } // if - if not started or not paused, do nothing 
} // Timer::unpause

Uint32 Timer::get_ticks()
{
    Uint32 time = 0;

    if (started)
    {
        if (paused)
        {
            time = paused_ticks;
        } // if - if the timer has been started and is currently paused
        else
        {
            time = SDL_GetTicks() - start_ticks;
        } // else - the timer is started and not paused 
    } // if the timer has not been started, the time is returned as its initial value, 0
    return time;
} // Timer::get_ticks
