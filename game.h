#ifndef GAME_H
#define GAME_H

// libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

// functionality
// #include "window.h"
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
#include "camera.h"

// entities
#include "dawg.h"
#include "desk.h"

// constants
#include "CONSTANTS.h"

using namespace std;

class Game
{

    public:

        Game(); // default constructor
        Game(string player_name, Window window); // explicit constructor



        // GAME LOGIC GOES HERE 


        // --------------------------------------------------------
        void start_game(int enemy_number); // start a new game
        // --------------------------------------------------------



        // accessors
        int get_enemies() const {return enemies;}; // get all enemies
        int get_active_enemies() const {return active_enemies;}; // get active enemies

        // game-play functions
        bool has_collided(Entity a, Entity b) const; // checks collision between two entities
        bool has_collided(SDL_Rect a, SDL_Rect b) const; // checks collision between two boxes
        bool has_collided(double x, double y, Entity b) const; // point collision with entity

        // interface handling
        void quit_game() {is_quit = true;}; // quits game
        void set_background(string media_path); // sets background from interface scope

    private:

        Player player;
        Window game_window;

        // game play data
        int enemies;
        int active_enemies;
        bool is_quit;
        bool player_died;
        bool victory;

        // FPS controls 
        Timer FPS_timer;
        double FPS_AVG;
};

#endif