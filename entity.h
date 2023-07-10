#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include "window.h"

using namespace std;

const int animation_frame_count = 4;

class Entity
{

    public: 

        Entity(); // default constructor

        void set_position_x(int x); // set x
        void set_position_y(int y); // set y
        int get_position_x() const; // get x
        int get_position_y() const; // get y
        SDL_Texture* get_texture() const {return sprite_sheet;}; // get texture
        SDL_Rect get_frame(int frame) const {return frames[frame];}; // get frames

    protected:

        int x; // position x
        int y; // posiiton y
        SDL_Texture* sprite_sheet;
        SDL_Rect frames[animation_frame_count];
};

#endif