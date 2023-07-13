#include "audio.h"

Audio::Audio()
{
    // iniitialize SDL audio mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
    {
        cout << "Failed to initialize SDL_mixer library: " << Mix_GetError() << endl;
    } // if
    audio = nullptr;
} // Audio::Audio

void Audio::load_audio(string media_path)
{
    audio = Mix_LoadWAV(media_path.c_str());
    if (audio == nullptr)
    {
        cout << "Failed to load audio: " << Mix_GetError() << endl;
        cout << "Audio path: " << media_path << endl;
    } // if
} // Audio::load_audio

void Audio::play() const
{
    Mix_PlayChannel(-1, audio, 0);
    // -1 represents channel, play at the nearest channel
    // audio is audio to be played
    // 0 is the amount of times to repeat play
} // Audio::play

