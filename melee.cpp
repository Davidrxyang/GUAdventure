#include "melee.h"

Melee::Melee() : Renderable()
{
    // none
} // default constructor

Melee::Melee(double ex, double ey, Window window)
{
    sprite_sheet = window.load_texture("assets/media/melee/hotdog.png", 0xFF, 0xFF, 0xFF);
    x = ex + 60;
    y = ey + 60;
    w = 200;
    h = 80;
    active = false;
    update_box();
} // explicit constructor

void Melee::attack(Renderable e)
{
    active = true;
    update_box();
} // Melee::attack

void Melee::render_melee(Window window, Camera camera)
{
    if (active)
    {
        render(window, camera);
    } // render if active
} // Melee::render_melee

void Melee::move(Renderable e)
{
    if (active)
    {
        x = e.get_x();
        y = e.get_y();

        switch(e.get_direction())
        {
            case UP:
            if (direction != UP)
            {
                y -= this -> h;
                flip = SDL_FLIP_NONE;
            } // if
            break;

            case DOWN:
            if (direction != DOWN)
            {
                y += e.get_h();
                flip = SDL_FLIP_VERTICAL;
            } // if 
            break;

            case LEFT:
            if (direction != LEFT)
            {
                x -= this -> w;
                flip = SDL_FLIP_NONE;
            } // if
            break;

            case RIGHT:
            if (direction != RIGHT)
            {
                x += e.get_w();
                flip = SDL_FLIP_HORIZONTAL;
            } // if
            break;

            default:
            break;
        } // switch
    } // if - active
    update_box();
} // Melee::move

void Melee::reset()
{
    active = false;
    direction = DEFAULT;
    x = 0; 
    y = 0;
} // Melee::reset

