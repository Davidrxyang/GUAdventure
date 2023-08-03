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

Dawg::Dawg(string name, double x, double y, GameMode mode, Window window) : Perishable()
{
    set_name(name);
    this -> x = x;
    this -> y = y;
    this -> mode = mode;
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
    Melee me(x, y, window);
    m = me;
} // explicit constructor

void Dawg::render(Window window, int frame, Camera camera)
{

    if (vx || vy)
    {
        Renderable::render(window, frame, camera);
        render_particles(window, camera);
        if (mode == projectile || mode == hybrid || mode == admin)
        {
            render_projectiles(window, camera);
        } // if - projectile
        if (mode == melee || mode == hybrid || mode == admin)
        {
            m.render_melee(window, camera);
        } // if - melee
        render_health(window, camera);
    } // render animation and trail if moving
    else
    {
        Renderable::render(window, 1, camera);
        if (mode == projectile || mode == hybrid || mode == admin)
        {
            render_projectiles(window, camera);
        } // if - projectile
        if (mode == melee || mode == hybrid || mode == admin)
        {
            m.render_melee(window, camera);
        } // if - melee
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
    m.attack(*this);
} // Dawg::melee_attack

void Dawg::reset_melee()
{
    m.reset();
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
                if (mode == projectile || mode == hybrid || mode == admin)
                {
                    fire_projectile(UP);
                } // if - mode check
                break;

                case SDLK_a:
                if (mode == projectile || mode == hybrid || mode == admin)
                {
                    fire_projectile(LEFT);
                } // if - mode check
                break;

                case SDLK_s:
                if (mode == projectile || mode == hybrid || mode == admin)
                {
                    fire_projectile(DOWN);
                } // if - mode check
                break;

                case SDLK_d:
                if (mode == projectile || mode == hybrid || mode == admin)
                {
                    fire_projectile(RIGHT);
                } // if - mode check
                break;

                case SDLK_t:
                if (mode == melee || mode == hybrid || mode == admin)
                {
                    melee_attack();
                } // if - mode check
                break;

                default:
                break;
            } // switch - process individual key event
        } // if - process event
        else if (e.type == SDL_KEYUP)
        {
            m.reset();
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
        if (mode == projectile || mode == hybrid || mode == admin)
        {
            for (size_t i = 0; i < TOTAL_PROJECTILES + 1; i++)
            {
                if (projectiles[i] -> is_active())
                {
                    projectiles[i] -> move(window, time_step);
                } // if - render if active
            } // for
        } // if - mode check
        if (mode == melee || mode == hybrid || mode == admin)
        {
            m.move(*this);
        } // if - mode check
    } // if - is alive 
} // Dawg::move


Dawg::~Dawg()
{
    for (size_t i = 0; i < TOTAL_PARTICLES; i++)
    {
        if (particles[i] != nullptr)
        {
            delete particles[i];
        } // if - allocated, deallocate
    } // for

    for (size_t i = 0; i < TOTAL_PROJECTILES + 1; i++)
    {
        if (projectiles[i] != nullptr)
        {
            delete projectiles[i];
        } // if - allocated, dellocate
    } // for 
} // destructor

