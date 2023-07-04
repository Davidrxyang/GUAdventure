#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
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

        bool load_media(string media_path); // load a media file
        
        SDL_Surface* load_surface(string media_path);
        void close_window(); // close the window
        
        
        bool test_run();

    private:
        
        // private functions

        SDL_Window* build_window(int, int, int, int);
        bool initialize() const;

        // window data dimensions

        int center_x;
        int center_y;
        int width;
        int height;
        string window_name;
        SDL_Window* window;

        SDL_Surface* background;

        SDL_Surface* temp_image;

        SDL_Surface* window_surface;
};

#endif