#include "interface.h"

Interface::Interface()
{
    // declares a global window
    Window g_window("Game", 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

    // builds game 
    Game game("David", g_window);

    int enemy_count = 40;
    game.start_game(enemy_count);
} // Interface::Interface