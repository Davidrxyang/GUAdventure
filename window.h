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
        
        void test_run() const;

    private:
        
        // private functions

        SDL_Window* build_window(string, int, int, int, int);
        void initialize() const;

        // window data dimensions

        int center_x;
        int center_y;
        int width;
        int height;
        string window_name;
        SDL_Window* window;

        SDL_Surface* window_surface;
};

#endif