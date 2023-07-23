#include "particle.h"

Particle::Particle()
{
    x = 0;
    y = 0;
    frame = 0;
    particle_texture = nullptr;
    red = nullptr;
    green = nullptr;
    blue = nullptr;
} // default constructor

Particle::Particle(int x, int y, Window window)
{
    load_textures(window);

    x = x - 5 + (rand() % 25);
    y = y - 5 + (rand() % 25); 

    frame = rand() % 5; // initialize frame

    switch(rand() % 3)
    {
        case 1:
        particle_texture = red;
        break;

        case 2:
        particle_texture = green;
        break;

        case 3:
        particle_texture = blue;
        break;
    } // randomize initial texture color
} // explicit constructor

void Particle::load_textures(Window window)
{
    red = window.load_texture("assets/media/particle/red.png");
    green = window.load_texture("assets/media/particle/green.png");
    blue = window.load_texture("assets/media/particle/blue.png");

    if (red == nullptr)
    {
        cout << "load failed";
    }
} // Particle::load_textures

void Particle::render(Window window)
{
    SDL_Rect target = {x, y, 10, 10};
    window.render(particle_texture, &target);
    frame++; // animate
} // Particle::render

bool Particle::is_dead()
{
    return frame > 10; // the particle has a life of 10 frames
} // Particle::is_dead