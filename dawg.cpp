#include "dawg.h"

Dawg::Dawg() : Perishable()
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
        particles.push_back(nullptr);
    } // initialize array to null

    for (size_t i = 0; i < TOTAL_PROJECTILES + 1; i++)
    {
        projectiles.push_back(nullptr);
    } // initalize projectiles to null

    projectile_counter = 0; 

} // default constructor

Dawg::Dawg(string name, double x, double y, Window window) : Perishable()
{
    set_name(name);
    this -> x = x;
    this -> y = y;
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
        particles.push_back(new Particle(x, y, window));
    } // initialize array of particles

    for (size_t i = 0; i < TOTAL_PROJECTILES + 1; i++)
    {
        projectiles.push_back(new Projectile(x, y, window));
    } // initalize projectiles

    projectile_counter = 0;

    // iniitailize melee weapon
    Melee m(x, y, window);
    melee = m;
} // explicit constructor

void Dawg::render(Window window, int frame, Camera camera)
{

    if (vx || vy)
    {
        Renderable::render(window, frame, camera);
        render_particles(window, camera);
        render_projectiles(window, camera);
        melee.render_melee(window, camera);
        render_health(window, camera);
    } // render animation and trail if moving
    else
    {
        Renderable::render(window, 1, camera);
        render_projectiles(window, camera);
        melee.render_melee(window, camera);
        render_health(window, camera);
    } // entity is stationary, no animation, fixed to frame 1
} // Dawg::render

void Dawg::render_particles(Window window, Camera camera)
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
} // Dawg::render_particles

void Dawg::render_projectiles(Window window, Camera camera)
{
    // render the particles
    for (size_t i = 0; i < TOTAL_PROJECTILES + 1; i++)
    {
        if (projectiles[i] -> is_active())
        {
            projectiles[i] -> render_projectile(window, camera);
        } // if - render if active
    } // for
} // Dawg::render_projectiles

void Dawg::fire_projectile(int current_projectile, Direction direction)
{
   projectiles[current_projectile] -> fire(x, y, direction);
} // Dawg::fire_projectile - private

void Dawg::fire_projectile()
{
    fire_projectile(projectile_counter, direction);

    if (projectile_counter == TOTAL_PROJECTILES)
    {
        projectiles[0] -> reset();
    } // if - set active false for finished projectile
    else
    {
        projectiles[projectile_counter + 1] -> reset();
    } // else 
    if (projectile_counter == TOTAL_PROJECTILES)
    {
        projectile_counter = 0;
    } // if - reset counter
    else
    {
        projectile_counter++;
    }
} // Dawg::fire_projectile

void Dawg::fire_projectile(Direction direction)
{
    fire_projectile(projectile_counter, direction);

    if (projectile_counter == TOTAL_PROJECTILES)
    {
        projectiles[0] -> reset();
    } // if - set active false for finished projectile
    else
    {
        projectiles[projectile_counter + 1] -> reset();
    } // else 
    if (projectile_counter == TOTAL_PROJECTILES)
    {
        projectile_counter = 0;
    } // if - reset counter
    else
    {
        projectile_counter++;
    }
} // Dawg::fire_projectile

void Dawg::kill_projectiles()
{
    for (size_t i = 0; i < TOTAL_PROJECTILES + 1; i++)
    {
        projectiles[i] -> reset();
    } // for
} // Dawg::kill_projectiles

void Dawg::melee_attack()
{
    Timer timer;
    melee.attack(*this);
} // Dawg::melee_attack

void Dawg::reset_melee()
{
    melee.reset();
} // Dawg::reset_melee

void Dawg::handle_event(SDL_Event& e)
{
    if (!dead)
    {
        Entity::handle_event(e);
        
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_w:
                fire_projectile(UP);
                break;

                case SDLK_a:
                fire_projectile(LEFT);
                break;

                case SDLK_s:
                fire_projectile(DOWN);
                break;

                case SDLK_d:
                fire_projectile(RIGHT);
                break;

                case SDLK_m:
                melee_attack();
                break;

                default:
                break;
            } // switch - process individual key event
        } // if - process event
        else if (e.type == SDL_KEYUP)
        {
            melee.reset();
        }
    } // handle event if alive
    else
    {
        kill_projectiles();
        kill();
    } // else - kill
} // Dawg::handle_event

void Dawg::move(Window window, double time_step)
{
    if (is_alive())
    {
        Entity::move(window, time_step);
        for (size_t i = 0; i < TOTAL_PROJECTILES + 1; i++)
        {
            if (projectiles[i] -> is_active())
            {
                projectiles[i] -> move(window, time_step);
            } // if - render if active
        } // for
        melee.move(*this);
    }
} // Dawg::move

/*
Dawg::~Dawg()
{
    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        delete particles[i];
    } // for

    for (size_t i = 0; i < TOTAL_PROJECTILES + 1; i++)
    {
        delete projectiles[i];
    } // for 
} // destructor
*/
