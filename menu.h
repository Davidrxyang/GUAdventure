#ifndef MENU_H
#define MENU_H

// libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

// functionality
#include "window.h"
#include "player.h"
#include "timer.h"
#include "text.h"
#include "file.h"

// tools
#include "audio.h"
#include "music.h"
#include "button.h"

// entities
#include "dawg.h"
#include "desk.h"

// constants
#include "CONSTANTS.h"

using namespace std;

class Menu
{

    public:

        Menu(); // default constructor
        Menu(Player* player, Window window); // explicit constructor
        ~Menu(); // quits SDL libraries if necessary
        
        MenuExitState start_menu(); // start menu

        void select_game(SDL_Event &e);
        void enter_player_name(SDL_Event &e);
        void select_player_type(SDL_Event &e);

        int poll_event(SDL_Event* e); // poll event
        void set_player(GameFile save);
        void new_game();
        void initialize();

        void render_title(); // renders "menu"
        void render_select_game();
        void render_enter_player_name(); // render epn
        void render_select_type();


    private:

        Player* player;
        Window menu_window;
        bool is_quit;
        MenuFunction function;
        GameFile save_1;
        GameFile save_2;
        GameFile save_3;
        GameFile save_4;
        GameFile save_5;

        int current_file;

        string player_name;
};

#endif