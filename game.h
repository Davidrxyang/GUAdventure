
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
const int GAME_SCREEN_HEIGHT = 600;
const int GAME_LEVEL_WIDTH = 3000;
const int GAME_LEVEL_HEIGHT = 1500;
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
        bool has_collided(SDL_Rect a, SDL_Rect b) const; // checks collision between two boxes
        bool has_collided(double x, double y, Entity b) const; // point collision with entity

        // test games
        void start_test_game_6(); // scrolling camera

    private:
        Player player;
        Window game_window;

        // FPS controls 
        Timer FPS_timer;
        double FPS_AVG;
};

#endif