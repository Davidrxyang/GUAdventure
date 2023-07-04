#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

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

        SDL_Surface* image;

        SDL_Surface* window_surface;
};

#endif