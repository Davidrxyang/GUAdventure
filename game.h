
/*

 this is the main file for the actual game
 main will simply call the constructor for game

 hopefully this will allow me to implement levels 
 locations easier later on ... 

 but we shall find out

*/

#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "dog.h"
#include "window.h"
#include "entity.h"
#include "player.h"

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Game
{
    public:
        Game(); // default constructor
        Game(string player_name); // explicit constructor
        void start_game(); // start a new game

    private:
        Player player;
        Window game_window;
};

#endif