#include "interface.h"

Interface::Interface()
{
    Window g_window("Game", 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    
    Game game("David", g_window);
    game.start_test_game_6();
}