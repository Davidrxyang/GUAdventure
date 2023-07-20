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
    collision_box.x = x;
    collision_box.y = y;
    collision_box.w = w;
    collision_box.h = h;
} // default constructor

void Entity::handle_event(SDL_Event &e)
{
    // initialize scancode key states
    const Uint8* current_key_states = SDL_GetKeyboardState(nullptr);

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        if (current_key_states[SDL_SCANCODE_UP])
        {
            vy = vy - 10;
        } // if        
        else if (current_key_states[SDL_SCANCODE_DOWN]) 
        {
            vy = vy + 10;
        } // else if
        else if (current_key_states[SDL_SCANCODE_RIGHT])
        {
            flip = SDL_FLIP_HORIZONTAL;
            vx = vx + 10;
        } // else if  
        else if (current_key_states[SDL_SCANCODE_LEFT])
        {
            flip = SDL_FLIP_NONE;
            vx = vx - 10;
        } // else if
    } // if - check event type

    // RESET VELOCITY WHEN THE KEY IS RELEASED

    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if (current_key_states[SDL_SCANCODE_UP])
        {
            vy = vy + 10;
        } // if        
        else if (current_key_states[SDL_SCANCODE_DOWN]) 
        {
            vy = vy - 10;
        } // else if
        else if (current_key_states[SDL_SCANCODE_RIGHT])
        {
            vx = vx - 10;
        } // else if  
        else if (current_key_states[SDL_SCANCODE_LEFT])
        {
            vx = vx + 10;
        } // else if
    } // if - check event type
} // Entity::handle_event

void Entity::move(Window window)
{
    // the w and h of the window is set to the global constants GAME_WIDTH and GAME_HEIGHT
    // in the game constructor
    
    x = x + vx;
    if ((x < 0) || (x + w > window.get_width()))
    {
        x = x - vx;
        vx = 0;
    } // if - at bounds, rebound

    y = y + vy;
    if (y < 0 || (y + h > window.get_height()))
    {
        y = y - vy;
        vy = 0;
    } // if - rebound
    
    update_box(); // update the collision box to follow entity movement
} // Entity::move

void Entity::stop()
{
    vx = 0;
    vy = 0;
} //  Entity::stop
