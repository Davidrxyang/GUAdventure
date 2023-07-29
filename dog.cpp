#include "dog.h"

Dog::Dog() : Perishable()
{
    name = "default name";
    x = 0;
    y = 0;
    w = 64;
    h = 205;
    update_box();
    update_health();

    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        particles[i] = nullptr;
    } // initialize array to null
} // default constructor

Dog::Dog(string name, Window window) : Perishable()
{
    set_name(name);
    x = 0;
    y = 0;
    w = 64;
    h = 205;
    update_box();
    update_health();
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
        particles[i] = new Particle(x, y, window);
    } // initialize array of particles
} // explicit constructor

void Dog::render_dog(Window window, int frame, Camera camera)
{

    if (vx || vy)
    {
        render(window, frame, camera);
        render_particles(window, camera);
        render_health(window, camera);
    } // render animation and trail if moving
    else
    {
        render(window, 1, camera);
        render_health(window, camera);
    } // entity is stationary, no animation, fixed to frame 1

    if (projectile.is_active())
    {
        projectile.render_projectile(window, camera);
        projectile.render_box(window, camera);
    }
} // Dog::render

void Dog::render_particles(Window window, Camera camera)
{
    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        if (particles[i] -> is_dead())
        {
            delete particles[i];
            particles[i] = new Particle(x, y + h, window); // offset y so particle is at foot
        } // if the particle is dead make a new particle
    } // for 

    // render the particles
    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        particles[i] -> render_particle(window, camera);
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

void Dog::fire_projectile(Window window)
{
    double pvx = 600;
    double pvy = 0;

    if (flip == SDL_FLIP_NONE)
    {
        pvx = -600;
    } // if - flip direction

    Projectile p(x, y, pvx, pvy, window);
    projectile = p;
    projectile.fire();

}