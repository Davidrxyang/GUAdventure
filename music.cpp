#include "music.h"

Music::Music() 
{
    // iniitialize SDL audio mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
    {
        cout << "Failed to initialize SDL_mixer library: " << Mix_GetError() << endl;
    } // if
    music = nullptr; 
} // default constructor

void Music::load_music(string media_path)
{
    music = Mix_LoadMUS(media_path.c_str());
    if (music == nullptr)
    {
        cout << "Failed to load music: " << Mix_GetError() << endl;
        cout << "Music path: " << media_path << endl;
    } // if
} // Music::load_music
void Music::play() const
{
    if (Mix_PlayingMusic() == 0) // the music is currently not playing
    {
        Mix_PlayMusic(music, -1);
    } // if
    else // if music is currently being playing
    {
        if (Mix_PausedMusic() == 1) // the music is currently paused
        {
            Mix_ResumeMusic(); // resume the music
        } // if
        // if the music is currently playing and not paused, do nothing
    } // else
} // Music::play

void Music::pause() const
{
    if (Mix_PlayingMusic() == 1) // music is currently playing
    {
        if (Mix_PausedMusic() == 0) // music not paused
        {
            Mix_PauseMusic();
        } // if
        // if music is paused, do nothing
    } // if
    // if music is not playing, do nothing
} // Music::pause

void Music::stop() const
{
    if (Mix_PlayingMusic() == 1)
    {
        Mix_HaltMusic(); // stop the music if it is playing, paused or not
    } // if
    // if the music is not playing, do nothing
} // Music::stop