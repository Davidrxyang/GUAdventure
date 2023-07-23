#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
#include <string>
#include "window.h"

using namespace std;

class Particle
{

    public:

        Particle(); // default constructor
        Particle(int x, int y, Window window); // explicit constructor

        void render(Window window); // render particle
        bool is_dead(); // if particle has dissapeared

    private:

        void load_textures(Window window); // private load textures

        int x; 
        int y;
        SDL_Texture* particle_texture;
        SDL_Texture* red;
        SDL_Texture* green;
        SDL_Texture* blue;
        int frame; // randomized internal frame count for animation

};
#endif