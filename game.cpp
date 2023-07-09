#include "game.h"

Game::Game() 
{
    // calls class default constructors
} // default constructor

Game::Game(string player_name) 
: game_window("Game")
{
    player.set_player_name(player_name);
} // explicit constructor

void Game::start_game()
{
    game_window.test_run_2();
} // Game::new_game