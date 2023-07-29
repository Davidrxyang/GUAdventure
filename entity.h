#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include "window.h"

const int TOTAL_PARTICLES = 10;
const double DEFAULT_SPEED = 640; // pixels per SECOND

using namespace std;

const int animation_frame_count = 4;

class Entity
{

    public: 

        Entity(); // default constructor

        int get_x() const {return x;}; // get x
        int get_y() const {return y;}; // get y
        int get_h() const {return h;}; // get h
        int get_w() const {return w;}; // get w
        SDL_Texture* get_texture() const {return sprite_sheet;}; // get texture
        SDL_Rect get_frame(int frame) const {return frames[frame];}; // get frames
        SDL_Rect get_box() const {return collision_box;}; // get collision box
        void handle_event(SDL_Event& e); // handle event input
        
        // Entity actions

        void spin(double a) {angle += a;}; // spin
        void move_x(int dx) {x += dx;}; // move x
        void move_y(int dy) {y += dy;}; // move y
        void set_vx(int vx) {this -> vx = vx;}; // velocity x
        void set_vy(int vy) {this -> vy = vy;}; // velocuty y
        void set_x(int x) {this -> x = x;}; // set x
        void set_y(int y) {this -> y = y;}; // set y

        void move(Window window, double time_step); // move entity

    protected:

        void update_box() {collision_box.x = x; collision_box.y = y;
                           collision_box.w = w; collision_box.h = h;} // update collision box

        double x; // position x
        double y; // posiiton y
        int w; // width
        int h; // height
        double vx; // velocity x
        double vy; // velocity y
        double angle; // rotation angle
        SDL_RendererFlip flip; // is flip?
        SDL_Texture* sprite_sheet; // sprite texture
        SDL_Rect frames[animation_frame_count]; // for animated sprites
        SDL_Rect collision_box; // collision box
        
};

#endif