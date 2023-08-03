#include "interface.h"

Interface::Interface()
{
    // declare a player
    Player* player = new Player(); 

    // declares a global window
    Window g_window("Game", 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT + DATA_PANEL_HEIGHT);


    // enters menu
    Menu menu(player, g_window); 
    MenuExitState m;

    m = menu.start_menu();
    GameFile current_file = menu.get_current_file();
    int file_number = menu.get_file_number();

    // set initial score
    int score = 0;

    // enter game upon successful menu exit
    if (m == menu_quit)
    {
        g_window.close_window();
    } // if - quit
    else if (m == menu_exit_success)
    {
        // builds game 
        Game game(player, g_window);

        size_t enemy_count = INITIAL_ENEMY_COUNT;
        size_t active_count = player -> get_remaining_enemies();
        size_t current_level = player -> get_level();
        GameEndState state;

        state = game.start_game(player); // start the first level

        while(state == game_victory)
        {
            current_level++;
            player -> set_level(current_level);
            player -> set_remaining_enemies(current_level * 10);
            state = game.start_game(player);
        } // while - keep winning, keep playing

        // after selecting quit game, leaves loop - SAVE GAME STATE BEFORE EXITING
        string file_path = "assets/data/s" + to_string(file_number) + ".txt";
        current_file.write(file_path, player -> get_player_name(), player -> get_mode(), player -> get_level(), 
        player -> get_score(), player -> get_remaining_enemies(), player -> get_health());

        // close window deallocates window objects and quits SDL libraries
        g_window.close_window(); 
    } // if - menu exit success, can begin game
} // Interface::Interface