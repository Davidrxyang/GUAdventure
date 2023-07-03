#include "entity.h"

Entity::Entity() 
{
    int x = 0;
    int y = 0;
} // default constructor

void Entity::set_position_x(int x) 
{
    this -> x = x;
} // Entity::set_position_x

void Entity::set_position_y(int y)
{
    this -> y = y;
} // Entity::set_position_y

int Entity::get_position_x() const
{
    return x;
} // Entity::get_position_x

int Entity::get_position_y() const
{
    return y;
} // Entity::get_position_y