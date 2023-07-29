#include "entity.h"

Entity::Entity() 
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    vx = 0;
    vy = 0;
    angle = 0;
    flip = SDL_FLIP_NONE;
    sprite_sheet = nullptr;
    collision_box.x = int(x);
    collision_box.y = int(y);
    collision_box.w = int(w);
    collision_box.h = int(h);
} // default constructor

void Entity::handle_event(SDL_Event &e)
{
    ///TODO - REIMPLEMENT VELOCITY BASED INPUT MOVEMENT HANDLING

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
            vy -= DEFAULT_SPEED;
            break;

            case SDLK_DOWN:
            vy += DEFAULT_SPEED;
            break;

            case SDLK_RIGHT:
            flip = SDL_FLIP_HORIZONTAL;
            vx += DEFAULT_SPEED; 
            break;

            case SDLK_LEFT:
            flip = SDL_FLIP_NONE;
            vx -= DEFAULT_SPEED;
            break;
        }
    } // if - check event type

    // RESET VELOCITY WHEN THE KEY IS RELEASED

    else if (e.type == SDL_KEYUP)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
            vy += DEFAULT_SPEED;
            break;

            case SDLK_DOWN:
            vy -= DEFAULT_SPEED;
            break;

            case SDLK_RIGHT:
            vx -= DEFAULT_SPEED; 
            break;

            case SDLK_LEFT:
            vx += DEFAULT_SPEED;
            break;
        }
    } // if - check event type
} // Entity::handle_event

void Entity::move(Window window, double time_step)
{
    // the w and h of the window is set to the global constants GAME_WIDTH and GAME_HEIGHT
    // in the game constructor

    x = x + vx * time_step; // standard physics equation x = x_0 + vt

    // modified bounds checking for time step movement
    if (x < 0)
    {
        x = 0;
        vx = 0;
    } // if
    else if (x + w > window.get_background_width())
    {
        x = window.get_background_width() - w;
        vx = 0;
    } // else if

    y = y + vy * time_step;
    if (y < 0)
    {
        y = 0;
        vy = 0;
    } // if
    else if (y + h > window.get_background_height())
    {
        y = window.get_background_height() - h;
        vy = 0;
    } // else if

    update_box(); // update the collision box to follow entity movement
} // Entity::move

void Entity::stop()
{
    vx = 0;
    vy = 0;
} //  Entity::stop

