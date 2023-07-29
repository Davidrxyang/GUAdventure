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

Projectile::Projectile(double ex, double ey, bool UP, bool LEFT, Window window)
{
    sprite_sheet = window.load_texture("assets/media/projectile/projectile.png", 0, 0xFF, 0xFF);

    x = ex + 50;
    y = ey + 50;
    vx = PROJECTILE_SPEED;
    
    if (UP)
    {
        vy *= -1;
    } // if 
    if (LEFT)
    {
        vx *= -1;
    } // if
    ey = 0; // TODO IMPLEMENT 2D PROJECTILE MOVEMENT
    w = 30;
    h = 30;
    active = false;
    update_box();
} // explicit constructor

void Projectile::fire()
{
    active = true;
}

void Projectile::render_projectile(Window window, Camera camera)
{
    render(window, camera);
} // Projectile::render_Projectile
