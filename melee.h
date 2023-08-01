#ifndef MELEE_H
#define MELEE_H

#include <SDL2/SDL.h>
#include <string>
#include <random>
#include "window.h"
#include "renderable.h"
#include "camera.h"

using namespace std;

class Melee : public Renderable
{

    public:

        Melee(); // default constructor
        Melee(double ex, double ey, Window window); // explicit constructor

        void attack(Renderable e); // attack
        void render_melee(Window window, Camera camera); // render Projectile with camera offset
        void move(Renderable e); // move
        void reset(); // reset
        bool is_active() const {return active;}; // is active
    private:

        bool active;

};
#endif