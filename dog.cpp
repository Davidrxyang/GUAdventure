#include "dog.h"

Dog::Dog() : Entity()
{
    name = "default name";
    sprite_sheet = nullptr;
} // default constructor

Dog::Dog(string name, Window window) : Entity()
{
    set_name(name);

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
    
} // explicit constructor

void Dog::set_name(string name)
{
    this -> name = name;
} // Dog::get_name

string Dog::get_name() const
{
    return name;
} // Dog::get_name

