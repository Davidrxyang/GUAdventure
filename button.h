#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <string>
#include "window.h"

#include "CONSTANTS.h"

using namespace std;


class Button
{

    public:
        Button(); // default constructor
        Button(int x, int y, int w, int h, Window window, string media_path); // explicit constructor with dimensions

        void set_position(int x, int y); // sets button position
        void set_texture(Window window, string media_path); // load buttont texture
        void handle_event(SDL_Event* event); // handle mouse event
        MouseState get_state() const {return current_state;}; // get current mouse state
        void render(Window window); // render in specified window
        
    private:

        int button_width; // button width
        int button_height; // button height
        SDL_Point position; // button position
        SDL_Texture* texture; // button texture
        MouseState current_state; // mouse state
};

#endif