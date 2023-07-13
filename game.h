
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
#include "button.h"
#include "audio.h"
#include "music.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

using namespace std;

class Game
{
    public:
        Game(); // default constructor
        Game(string player_name); // explicit constructor
        void start_game(); // start a new game
        
        void TEST_TEMPLATE(); // template for test games

        // test games
        void start_test_game_1(); // test V1
        void start_test_game_2(); // test V2


    private:
        Player player;
        Window game_window;
        Dog jack;
};

#endif