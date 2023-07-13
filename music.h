#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

class Music 
{

    public:
    
        Music(); // default constructor
        void load_music(string media_path); // load music
        void play() const; // play music
        void pause() const; // pause music
        void stop() const; // stop music

    private:

        Mix_Music* music;
};
#endif