
/*

 this is the main file for the actual game
 main will simply call the constructor for game

 hopefully this will allow me to implement levels 
 locations easier later on ... 

 but we shall find out

*/

#ifndef GAME_H
#define GAME_H

// libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

// functionality
#include "level.h"
#include "window.h"
#include "entity.h"
#include "renderable.h"
#include "perishable.h"
#include "player.h"
#include "timer.h"
#include "text.h"

// tools
#include "audio.h"
#include "music.h"
#include "button.h"
#include "camera.h" // camera is currently unused, saved for level scrolling functionality

// entities
#include "dog.h"
#include "desk.h"

// constants

const int GAME_SCREEN_WIDTH = 1400;
const int GAME_SCREEN_HEIGHT = 1000;
const int GAME_LEVEL_WIDTH = 3000;
const int GAME_LEVEL_HEIGHT = 2000;
const SDL_Color DEFAULT_BLACK = {0, 0, 0};

using namespace std;

class Game
{

    public:
        Game(); // default constructor
        Game(string player_name); // explicit constructor
        void start_game(); // start a new game
        
        // game-play functions
        bool has_collided(Entity a, Entity b) const; // checks collision between two entities

        void TEST_TEMPLATE(); // template for test games

        // test games
        void start_test_game_1(); // audio testing, button testing
        void start_test_game_2(); // frame rate timer
        void start_test_game_3(); // text entity 
        void start_test_game_4(); // file I/O
        void start_test_game_5(); // jack has particles
        void start_test_game_6(); // scrolling camera

    private:
        Player player;
        Window game_window;

        // character entities
        Dog jack;

        // FPS controls 
        Timer FPS_timer;
        double FPS_AVG;
};

#endif