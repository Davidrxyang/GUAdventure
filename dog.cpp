#include "dog.h"

Dog::Dog() : Entity()
{
    name = "default name";
} // default constructor

Dog::Dog(string name) : Entity()
{
    set_name(name);
} // explicit constructor

void Dog::set_name(string name)
{
    this -> name = name;
} // Dog::get_name

string Dog::get_name() const
{
    return name;
} // Dog::get_name