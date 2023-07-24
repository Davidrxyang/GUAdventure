#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
#include <string>
#include <random>
#include "window.h"
#include "camera.h"

using namespace std;

class Particle
{

    public:

        Particle(); // default constructor
        Particle(int entity_x, int entity_y, Window window); // explicit constructor

        void render_particle(Window window); // render particle
        void render_particle(Window window, Camera camera); // render particle with camera offset

        bool is_dead(); // if particle has dissapeared
        void set_life(int life); // sets the lifespan

    private:

        void load_textures(Window window); // private load textures

        int x; 
        int y;
        int life; // lifespan of the particle
        SDL_Texture* particle_texture;
        SDL_Texture* red;   
        SDL_Texture* green;
        SDL_Texture* blue;
        int frame; // randomized internal frame count for animation

};
#endif