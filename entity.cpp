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
    direction = DEFAULT;
    sprite_sheet = nullptr;
    collision_box.x = int(x);
    collision_box.y = int(y);
    collision_box.w = int(w);
    collision_box.h = int(h);
} // default constructor

void Entity::handle_event(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
            vy -= DEFAULT_SPEED;
            direction = UP;
            break;

            case SDLK_DOWN:
            vy += DEFAULT_SPEED;
            direction = DOWN;
            break;

            case SDLK_RIGHT:
            flip = SDL_FLIP_HORIZONTAL;
            vx += DEFAULT_SPEED; 
            direction = RIGHT;
            break;

            case SDLK_LEFT:
            flip = SDL_FLIP_NONE;
            vx -= DEFAULT_SPEED;
            direction = LEFT;
            break;
        }
    } // if - check event type

    // RESET VELOCITY WHEN THE KEY IS RELEASED

    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
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
    } // if
    else if (x + w > window.get_background_width())
    {
        x = window.get_background_width() - w;
    } // else if

    y = y + vy * time_step;
    if (y < 0)
    {
        y = 0;
    } // if
    else if (y + h > window.get_background_height())
    {
        y = window.get_background_height() - h;
    } // else if

    update_box(); // update the collision box to follow entity movement
} // Entity::move

void Entity::collision_rebound()
{
    if (direction == UP)
    {
        move_y(REBOUND_DISTANCE);
    } // if
    else if (direction == DOWN)
    {
        move_y(-REBOUND_DISTANCE);
    } // else if 
    else if (direction == RIGHT)
    {
        move_x(-REBOUND_DISTANCE);
    } // else if
    else if (direction == LEFT)
    {
        move_x(REBOUND_DISTANCE);
    } // else if 
} // Entity::collision_rebound

void Entity::collision_rebound(double rebound_distance)
{
    if (direction == UP)
    {
        move_y(rebound_distance);
    } // if
    else if (direction == DOWN)
    {
        move_y(-rebound_distance);
    } // else if 
    else if (direction == RIGHT)
    {
        move_x(-rebound_distance);
    } // else if
    else if (direction == LEFT)
    {
        move_x(rebound_distance);
    } // else if 
} // Entity::collision_rebound

void Entity::orient(Direction edirection)
{
    switch(edirection)
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
            y += this -> h;
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
            x += this -> w;
            flip = SDL_FLIP_HORIZONTAL;
        } // if
        break;

        default:
        break;
    } // switch - direction change
    update_box();
    direction = edirection;
} // Entity::orient

