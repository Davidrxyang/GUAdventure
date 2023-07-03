#include "level.h"

Level::Level()
{
    name = "default name";
} // default constructor

Level::Level(string name)
{
    set_name(name);
} // explicit constructor

void Level::set_name(string name)
{
    this -> name = name;
} // Level::set_name

string Level::get_name() const
{
    return name;
} // Level::get_name