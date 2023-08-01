#include "projectile.h"

Projectile::Projectile() : Renderable()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    vx = 0;
    vy = 0;
    active = false;
    update_box();
} // default constructor

Projectile::Projectile(double ex, double ey, Window window)
{
    sprite_sheet = window.load_texture("assets/media/projectile/projectile.png", 0, 0xFF, 0xFF);

    x = ex + 50;
    y = ey + 50;
    vx = 0;

    vy = 0; 
    w = 30;
    h = 30;
    active = false;
    update_box();
} // explicit constructor

void Projectile::fire(double ex, double ey, Direction direction)
{
    // fire projectile - stationary becomes moving, with direction parameters
    vx = 0;
    vy = 0;
    
    if (direction == UP)
    {
        vy = PROJECTILE_SPEED;
        vy *= -1;
    } // else if 
    else if (direction == DOWN)
    {
        vy = PROJECTILE_SPEED;
    } // else if 
    else if (direction == LEFT)
    {
        vx = PROJECTILE_SPEED;
        vx *= -1;
    } // else if
    else if (direction == RIGHT)
    {
        vx = PROJECTILE_SPEED;
    } // else if 

    x = ex;
    y = ey;

    active = true;
} // Projectile::fire

void Projectile::reset() 
{
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    active = false;
    direction = DEFAULT;
    update_box();
} // Projectile::reset

void Projectile::move(Window window, double time_step)
{
    // overloaded function is same as entity::move, but out of bounds results in projectile reset
    x = x + vx * time_step; // standard physics equation x = x_0 + vt
    y = y + vy * time_step;

    // modified bounds checking for time step movement
    if (x < 0
    || x + w > window.get_background_width()
    || y < 0
    || y + h > window.get_background_height())
    {
        reset();
    } // if
    update_box(); // update the collision box to follow entity movement  
} // Projectile::move

void Projectile::render_projectile(Window window, Camera camera)
{
    render(window, camera);
} // Projectile::render_Projectile
