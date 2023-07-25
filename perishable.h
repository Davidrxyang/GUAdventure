#ifndef PERISHABLE_H
#define PERISHABLE_H

#include "SDL2/SDL.h"
#include "renderable.h"
#include "camera.h"
#include "window.h"

#include <iostream>

using namespace std;

const int MAX_HEALTH = 10;
const int HEALTH_BAR_UNIT_LENGTH = 8;
const int HEALTH_BAR_HEIGHT = 10;

// TODO set constant health bar frame and bar colors, red and black 

class Perishable : public Renderable
{

    public:

        Perishable(); // default constructor
        Perishable(int initial_health, bool is_dead); // explicit constructor
        bool is_dead() const {return is_dead;}; // if the entity is dead
        int get_health() const {return health;}; // get health
        void kill() {health = 0;}; // kills the entity
        void change_health(int n); // change health by n, with bounds checking, n can be POS or NEG

        void render_health(Window window) const; // render health bar
        void render_health(Window window, Camera camera) const; // render health bar with cam offset

    protected:

        int health;
        SDL_Rect health_bar_frame;
        SDL_Rect health_bar;
        bool is_dead;
};

#endif