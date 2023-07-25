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
        Perishable(int initial_health, bool is_dead); // explicit constructor
        bool died() const {return is_dead;}; // if the entity is dead
        int get_health() const {return health;}; // get health
        void kill() {health = 0;}; // kills the entity
        void change_health(int n); // change health by n, with bounds checking, n can be POS or NEG

        void render_health(Window window); // render health bar
        void render_health(Window window, Camera camera); // render health bar with cam offset

    protected:

        void update_health(); // update health bar position

        int health;
        SDL_Rect health_bar_frame;
        SDL_Rect health_bar;
        bool is_dead;
};

#endif