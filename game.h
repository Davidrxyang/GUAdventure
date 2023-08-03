#ifndef GAME_H
#define GAME_H

// libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <cmath>

// functionality
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
        Game(Player* player, Window window); // explicit constructor


        // GAME LOGIC GOES HERE 


        // --------------------------------------------------------
        GameEndState start_game(Player* player); // start a new game, return end state when quit
        // --------------------------------------------------------



        // modifiers
        size_t get_enemies() const {return enemies;}; // get all enemies
        size_t get_active_enemies() const {return active_enemies;}; // get active enemies
        void set_current_level(size_t level) {current_level = level;}; // set level counter
        size_t get_current_level() const {return current_level;}; // gets level counter

        // game-play functions
        bool has_collided(Entity a, Entity b) const; // checks collision between two entities
        bool has_collided(SDL_Rect a, SDL_Rect b) const; // checks collision between two boxes
        bool has_collided(double x, double y, Entity b) const; // point collision with entity
        double get_distance(Entity a, Entity b) const; // returns distance between two entities

        // game handling
        void quit_game() {is_quit = true;}; // quits game
        void set_background(string media_path); // sets background from interface scope
        void handle_game_event(SDL_Event &e); // handles game event like pause, quit
        void process_end_game(); // sets game state on end game
        void set_enemy_speed(double speed); // sets enemy speed externally from interface
        void increase_enemy_speed(double speed); // sets enemy speed externally from interface
        void render_data_panel(int current_health); // renders data panel
        int poll_event(SDL_Event* e); // poll event
        void loading(); // enter loading screen
    private:

        Player* player;
        Window game_window;

        // game play data
        int enemies;
        int active_enemies;
        bool is_quit;
        bool is_paused;
        bool player_died;
        bool victory;
        bool can_continue;
        GameEndState state;
        double dawg_speed_mid;
        size_t current_level;

        // game mode
        GameMode mode;

        // interface objects
        SDL_Texture* loading_screen;

        // FPS controls 
        Timer FPS_timer;
        double FPS_AVG;
};

#endif