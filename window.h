#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

//#include "game.h"

using namespace std;

enum KeyPress
{
    key_default,
    key_up,
    key_down,
    key_left,
    key_right,
    key_total,
};

class Window
{


    public:

        Window(); // constructor
        Window(string name); // create a default window
        Window(string name, int x, int y, int w, int h); // window with specified dimensions
        
        void set_name(string name);

        bool set_background(string media_path); // loads background texture
        bool load_media(); // load preset media files
        bool load_media(string media_path); // load a specfic media file
        
        SDL_Surface* load_surface(string media_path); // TODO implement format optimization
        SDL_Texture* load_texture(string media_path); // load a fast SDL texture
        void close_window(); // close the window
        
        
        bool test_run();

    private:
        
        // private functions

        SDL_Window* build_window(int, int, int, int); // builds window
        SDL_Renderer* build_renderer(SDL_Window* temp_window); // builds renderer for specified window
        bool initialize() const;

        // window data dimensions

        int center_x;
        int center_y;
        int width;
        int height;
        string window_name;
        SDL_Window* window;
        SDL_Window* t_window;

        SDL_Renderer* renderer;
        
        SDL_Texture* background;
        SDL_Texture* texture;
        SDL_Surface* temp_image;
        SDL_Surface* window_surface;
        SDL_Surface* KeyPress[key_total]; // array for corresponding keypress surfaces, testing
        SDL_Rect rect;
};

#endif