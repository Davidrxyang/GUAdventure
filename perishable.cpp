#include "perishable.h"

Perishable::Perishable() : Renderable()
{
    int health = MAX_HEALTH;
    SDL_Rect frame = {int(x), int(y), MAX_HEALTH * HEALTH_BAR_UNIT_LENGTH, HEALTH_BAR_HEIGHT}; 
    SDL_Rect bar = {int(x), int(y), health * HEALTH_BAR_UNIT_LENGTH, HEALTH_BAR_HEIGHT};
    is_dead = false;

    health_bar_frame = frame;
    health_bar = bar;
} // default constructor

Perishable::Perishable(int initial_health, bool is_dead) : Renderable()
{
    int health = initial_health;
    SDL_Rect frame = {int(x), int(y), MAX_HEALTH * HEALTH_BAR_UNIT_LENGTH, HEALTH_BAR_HEIGHT}; 
    SDL_Rect bar = {int(x), int(y), health * HEALTH_BAR_UNIT_LENGTH, HEALTH_BAR_HEIGHT};
    this -> is_dead = is_dead;

    health_bar_frame = frame;
    health_bar = bar;
} // explicit constructor

void Perishable::change_health(int n)
{
    if (health + n < 0 || health + n > MAX_HEALTH)
    {
        cout << "Failed to change health: invalid health" << endl;
    } // if - health change is invalid
    else
    {
        health += n;
    } // else - health change is valid
} // Perishable::change_health - the change amount can be POSITIVE OR NEGATIVE, but usually negative 

void Perishable::render_health(Window window)
{
    update_health();

    // render a filled rectangle as background, white
    SDL_SetRenderDrawColor(window.get_renderer(), 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(window.get_renderer(), &health_bar_frame);
    
    // render a filled rectangle, set color red first
    SDL_SetRenderDrawColor(window.get_renderer(), 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(window.get_renderer(), &health_bar);
    
    // render an unfilled rectangle frame, set color black
    SDL_SetRenderDrawColor(window.get_renderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(window.get_renderer(), &health_bar_frame);
} // Perishable::render_health

void Perishable::render_health(Window window, Camera camera)
{
    update_health();

    // handling camera offsets
    SDL_Rect temp_frame = health_bar_frame;
    temp_frame.x -= camera.get_x();
    temp_frame.y -= camera.get_y();

    SDL_Rect temp_bar = health_bar;
    temp_bar.x -= camera.get_x();
    temp_bar.y -= camera.get_y();  

    // render a filled rectangle as background, white
    SDL_SetRenderDrawColor(window.get_renderer(), 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(window.get_renderer(), &temp_frame);
    
    // render a filled rectangle, set color red first
    SDL_SetRenderDrawColor(window.get_renderer(), 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(window.get_renderer(), &temp_bar);
    
    // render an unfilled rectangle frame, set color black
    SDL_SetRenderDrawColor(window.get_renderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(window.get_renderer(), &temp_frame);
} // Perishable::render_health

void Perishable::update_health()
{
    health_bar_frame.x = int(x);
    health_bar_frame.y = int(y);
    health_bar.x = int(x);
    health_bar.y = int(y);
}


