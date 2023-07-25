#include "perishable.h"

Perishable::Perishable() : Renderable()
{
    int health = MAX_HEALTH;
    SDL_Rect health_bar_frame = {x, y, MAX_HEALTH * HEALTH_BAR_UNIT_LENGTH, HEALTH_BAR_HEIGHT}; 
    SDL_Rect health_bar = {x, y, health * HEALTH_BAR_UNIT_LENGTH, HEALTH_BAR_HEIGHT};
    is_dead = false;
} // default constructor

Perishable::Perishable(int initial_health, bool is_dead) : Renderable()
{
    int health = initial_health;
    SDL_Rect health_bar_frame = {x, y, MAX_HEALTH * HEALTH_BAR_UNIT_LENGTH, HEALTH_BAR_HEIGHT}; 
    SDL_Rect health_bar = {x, y, health * HEALTH_BAR_UNIT_LENGTH, HEALTH_BAR_HEIGHT};
    this -> is_dead = is_dead;
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

void render_health(Window window)
{
    // use special rendering method for SDL rect, will have to re-implement camera offset calculations...
}
