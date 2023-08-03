#include "desk.h"

Desk::Desk() : Renderable()
{
    name = "default name";
    x = 0;
    y = 0;
    w = 64;
    h = 205;
    collision_box.x = x;
    collision_box.y = y;
    collision_box.w = w;
    collision_box.h = h;
} // default constructor

Desk::Desk(string name, double x, double y, Window window) : Renderable()
{
    set_name(name);
    this -> x = x;
    this -> y = y;
    w = 400;
    h = 200;
    collision_box.x = x;
    collision_box.y = y;
    collision_box.w = w;
    collision_box.h = h;
    sprite_sheet = window.load_texture("assets/media/desk.png", 0xFF, 0xFF, 0xFF);
    // loads sprite sheet 
} // explicit constructor

