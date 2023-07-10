#include "game.h"

Game::Game() 
{
    // calls class default constructors
} // default constructor

Game::Game(string player_name) 
: game_window("Game")
{
    this -> jack = Dog("jack", game_window);
    // Window game_window("Game");
    player.set_player_name(player_name);
} // explicit constructor

void Game::start_game()
{
    bool isquit = false;

    game_window.set_background("media/red_brick.png");
    int frame = 0;
    SDL_Rect target = {100, 100, 100, 100};
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
        
        SDL_Rect current_frame = jack.get_frame(frame/4);
        
        game_window.render_clear();
        game_window.render(game_window.get_background());
        game_window.render(jack.get_texture(), &target, &current_frame);
        game_window.update_screen();
        
        frame++;

        if (frame/4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        }
    }
} // Game::new_game