#include "interface.h"

Interface::Interface()
{
    // declares a global window
    Window g_window("Game", 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT + DATA_PANEL_HEIGHT);

    // builds game 
    Game game("David", g_window);

    size_t enemy_count = INITIAL_ENEMY_COUNT;
    size_t current_level = 0;
    GameEndState state;

    current_level = 1;
    game.set_current_level(current_level);
    state = game.start_game(enemy_count); // start the first level

    while(state == game_victory)
    {
        current_level++;
        // enemy_count *= ENEMY_COUNT_INCREMENT_FACTOR;
        enemy_count += 10;
        game.set_current_level(current_level);
        state = game.start_game(enemy_count);

        if (current_level > 2)
        {
            game.increase_enemy_speed(100);
            enemy_count -= 5;
        } // if - after level three, increase speed, increase enemy count by less
    } // while - keep winning, keep playing
} // Interface::Interface