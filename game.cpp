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
    bool isquit = false;

    game_window.set_background("media/red_brick.png");


    SDL_Event game_event;
    while(!isquit)
    {
        if (SDL_PollEvent(& game_event))
        {
            if (game_event.type == SDL_QUIT)
            {
                isquit = true;
            }
        }
        game_window.render_clear();
        game_window.render(game_window.get_background());
        game_window.update_screen();
    }
} // Game::new_game