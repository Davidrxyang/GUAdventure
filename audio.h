#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

class Audio
{

    public:
        Audio(); // default constructor
        void load_audio(string media_path); // load audio
        void play() const; // play audio

    private:
        Mix_Chunk* audio;
};

#endif