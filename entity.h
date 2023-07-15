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

        void set_position_x(int x) {this -> x = x;}; // set x
        void set_position_y(int y) {this -> y = y;}; // set y
        int get_position_x() const {return x;}; // get x
        int get_position_y() const {return y;}; // get y
        SDL_Texture* get_texture() const {return sprite_sheet;}; // get texture
        SDL_Rect get_frame(int frame) const {return frames[frame];}; // get frames
        SDL_Rect get_box() const {return collision_box;}; // get collision box
        void handle_event(SDL_Event& e); // handle event input
        
        // Entity actions

        void spin(double a) {angle += a;}; // spin
        void move(Window window); // move entity
        void stop(); // stop entity - resets velocity

    protected:

        void update_box() {collision_box.x = x; collision_box.y = y;} // update collision box

        int x; // position x
        int y; // posiiton y
        int w; // width
        int h; // height
        int vx; // velocity x
        int vy; // velocity y
        double angle; // rotation angle
        SDL_RendererFlip flip; // is flip?
        SDL_Texture* sprite_sheet; // sprite texture
        SDL_Rect frames[animation_frame_count]; // for animated sprites
        SDL_Rect collision_box; // collision box
        
};

#endif