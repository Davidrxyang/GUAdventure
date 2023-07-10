#include "dog.h"

Dog::Dog() : Entity()
{
    name = "default name";
    sprite_sheet = nullptr;
} // default constructor

Dog::Dog(string name, Window window) : Entity()
{
    set_name(name);

    sprite_sheet = window.load_texture("media/man.png", 0, 0xFF, 0xFF);
    // loads sprite sheet with cyan background

} // explicit constructor

void Dog::set_name(string name)
{
    this -> name = name;
} // Dog::get_name

string Dog::get_name() const
{
    return name;
} // Dog::get_name

