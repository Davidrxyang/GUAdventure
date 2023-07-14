#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include "window.h"

using namespace std;

class Timer
{

    public: 

        Timer(); // default constructor

        void start();
        void stop();
        void pause();
        void unpause();

        Uint32 get_ticks() const; // get time
        double get_seconds() const {return (get_ticks() / 1000.f);}; // get time in seconds

        bool is_started() const {return started;}; 
        bool is_paused() const {return started && paused;};

    private:

        Uint32 start_ticks; 
        Uint32 paused_ticks;
        bool paused;
        bool started;
};

#endif