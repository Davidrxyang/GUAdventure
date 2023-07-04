#include "player.h"

Player::Player()
{
    set_player_name("default name");
} // default constructor

Player::Player(string name)
{
    set_player_name(name);
} // explicit constructor

void Player::set_player_name(string name)
{
    this -> player_name = name;
} // Player::set_player_name

string Player::get_player_name() const
{
    return player_name;
} // Player::get_player_name