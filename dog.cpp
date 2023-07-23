#include "dog.h"

Dog::Dog() : Renderable()
{
    name = "default name";
    x = 0;
    y = 0;
    w = 64;
    h = 205;
    collision_box.x = x;
    collision_box.y = y;
    collision_box.w = w;
    collision_box.h = h;

    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        particles[i] = nullptr;
    } // initialize array to null
} // default constructor

Dog::Dog(string name, Window window) : Renderable()
{
    set_name(name);
    x = 0;
    y = 0;
    w = 64;
    h = 205;
    collision_box.x = x;
    collision_box.y = y;
    collision_box.w = w;
    collision_box.h = h;
    sprite_sheet = window.load_texture("assets/media/man.png", 0, 0xFF, 0xFF);
    // loads sprite sheet with cyan background

    frames[0].x =   0;
    frames[0].y =   0;
    frames[0].w =  64;
    frames[0].h = 205;

    frames[1].x =  64;
    frames[1].y =   0;
    frames[1].w =  64;
    frames[1].h = 205;
        
    frames[2].x = 128;
    frames[2].y =   0;
    frames[2].w =  64;
    frames[2].h = 205;

    frames[3].x = 192;
    frames[3].y =   0;
    frames[3].w =  64;
    frames[3].h = 205;    

    w = 64;
    h = 205;

    // initialize particles
    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        Particle particle(x, y, window);
        particles[i] = &particle;
    } // initialize array of particles
} // explicit constructor

void Dog::render_dog(Window window, int frame)
{
    render(window, frame);
    render_particles(window);
} // Dog::render

void Dog::render_particles(Window window)
{
    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        if (particles[i] -> is_dead())
        {
            //delete particles[i];
            //particles[i] = new Particle(x, y, window);
        } // if the particle is dead make a new particle
    } // for 

    // render the particles
    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        particles[i] -> render(window);
    } // for
} // Dog::render_particles

/*
Dog::~Dog()
{
    //Delete particles
    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        delete particles[i];
    } // for
} // destructor

*/