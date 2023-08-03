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
        
        // start menu
        MenuExitState start_menu(); // start menu

        // menu function levels
        void select_game(SDL_Event &e);
        void enter_player_name(SDL_Event &e);
        void select_player_type(SDL_Event &e);
        void delete_save(SDL_Event &e);
        void admin_pwd(SDL_Event &e);
        void complete(SDL_Event &e);

        GameFile get_current_file() const; // get current file
        int get_file_number() const {return current_file;}; // file number
        string mode_to_text(GameMode mode) const; // converter

        // menu methods
        int poll_event(SDL_Event* e); // poll event
        void set_player(GameFile save);
        void new_game();
        void initialize();

        // menu rendering
        void render_title(); // renders "menu"
        void render_select_game();
        void render_enter_player_name(); // render epn
        void render_select_type();
        void render_delete_save();
        void render_admin_pwd();
        void render_complete();


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
        string pwd;
};

#endif