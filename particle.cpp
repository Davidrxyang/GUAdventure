#include "particle.h"

Particle::Particle()
{
    x = 0;
    y = 0;
    frame = 0;
    life = 20;
    particle_texture = nullptr;
    red = nullptr;
    green = nullptr;
    blue = nullptr;
} // default constructor

Particle::Particle(int entity_x, int entity_y, Window window)
{
    load_textures(window);

    x = entity_x - 5 + (rand() % 25);
    y = entity_y - 5 + (rand() % 25); 
    life = 20;
    frame = rand() % 5; // initialize frame

    switch(rand() % 3)
    {
        case 0:
        particle_texture = red;
        break;

        case 1:
        particle_texture = green;
        break;

        case 2:
        particle_texture = blue;
        break;
    } // randomize initial texture color
} // explicit constructor

void Particle::load_textures(Window window)
{
    red = window.load_texture("assets/media/particle/red.png", 0, 0xFF, 0xFF);
    green = window.load_texture("assets/media/particle/green.png", 0, 0xFF, 0xFF);
    blue = window.load_texture("assets/media/particle/blue.png", 0, 0xFF, 0xFF);
} // Particle::load_textures

void Particle::render_particle(Window window)
{
    SDL_Rect target = {x, y, 20, 20};
    window.render(particle_texture, &target);
    frame++; // animate
} // Particle::render

bool Particle::is_dead()
{
    return frame > life; // the particle has a life of 10 frames
} // Particle::is_dead