#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <string>
#include <random>
#include "window.h"
#include "renderable.h"
#include "camera.h"

using namespace std;

class Projectile : public Renderable
{

    public:

        Projectile(); // default constructor
        Projectile(double ex, double ey, double evx, double evy, Window window); // explicit constructor

        void fire();
        void render_projectile(Window window, Camera camera); // render Projectile with camera offset
        bool is_active() const {return active;}; // is active
        void set_active(bool b) {active = b;}; // set active

    private:

        bool active;
};
#endif