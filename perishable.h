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

class Perishable : public Renderable
{

    public:

        Perishable(); // default constructor
        Perishable(int initial_health, bool dead); // explicit constructor
        bool is_dead() const {return dead;}; // if the entity is dead
        bool is_alive() const {return !dead;}; // if the entity is alive
        int get_health() const {return health;}; // get health
        void kill(); // kills the entity
        void change_health(int n); // change health by n units, pos or neg

        void render_health(Window window); // render health bar
        void render_health(Window window, Camera camera); // render health bar with cam offset
        
    protected:

        void update_health(); // update health bar position

        int health;
        SDL_Rect health_bar_frame;
        SDL_Rect health_bar;
        bool dead;
};

#endif