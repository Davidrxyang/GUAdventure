#ifndef PERISHABLE_H
#define PERISHABLE_H

#include "SDL2/SDL.h"
#include "renderable.h"
#include "camera.h"
#include "window.h"
#include <iostream>

#include "CONSTANTS.h"

using namespace std;

class Perishable : public Renderable
{

    public:

        Perishable(); // default constructor
        Perishable(int initial_health, bool dead); // explicit constructor
        bool is_dead() const {return dead;}; // if the entity is dead
        bool is_alive() const {return !dead;}; // if the entity is alive
        int get_health() const {return health;}; // get health
        void kill(); // kills the entity
        HealthState change_health(int n); // change health by n units, pos or neg

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