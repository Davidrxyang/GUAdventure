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
    game_window.set_font("fonts/font.ttf", 20, 0, 0xFF, 0xFF);
    game_window.set_local_text("sup fellas");
    int frame = 0;
    int x = 200;
    int y = 200;
    SDL_Rect target = {x, y, 100, 100};
    SDL_Rect text_target = {300, 300, 200, 200};
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;

    Button buttons[4];
    // setting button positions
    buttons[0].set_position(0, 0);
    buttons[1].set_position(400,0);
    buttons[2].set_position(0,400);
    buttons[3].set_position(400,400);

    for (size_t i = 0; i < 4; i++)
    {
        buttons[i].set_texture(game_window, "media/buttons.png");
    } // for

    while(!isquit)
    {
        if (SDL_PollEvent(& game_event))
        {
            if (game_event.type == SDL_QUIT)
            {
                isquit = true;
            }
            else if (game_event.type == SDL_KEYDOWN)
            {
                switch (game_event.key.keysym.sym)
                {
                    case SDLK_f:
                    flip = SDL_FLIP_HORIZONTAL;
                    break;

                    case SDLK_b:
                    flip = SDL_FLIP_NONE;
                    break;

                    case SDLK_l:
                    angle = angle + 60;
                    break;

                    case SDLK_r:
                    angle = angle - 60;
                    break;

                    case SDLK_UP:
                    y = y - 20;
                    break;

                    case SDLK_DOWN:
                    y = y + 20;
                    break;

                    case SDLK_RIGHT:
                    flip = SDL_FLIP_HORIZONTAL;
                    x = x + 20;
                    break;

                    case SDLK_LEFT:
                    flip = SDL_FLIP_NONE;
                    x = x - 20;
                    break;

                    case SDLK_q: // quit program
                    isquit = true;
                    break;
                } // switch
            } // else if
            else // mouse event
            {
                for (size_t i = 0; i < 4; i++)
                {
                    buttons[i].handle_event(&game_event);
                }
            }
        } // if - game event poll check
        
        SDL_Rect current_frame = jack.get_frame(frame/8);
    
        target.x = x;
        target.y = y;
        
        game_window.render_clear();
        game_window.render(game_window.get_background());
        // game_window.render(game_window.get_text(), &text_target);
        game_window.render(jack.get_texture(), &target, &current_frame, angle, nullptr, flip);
        
        //render buttons
        for (size_t i = 0; i < 4; i++)
        {
            buttons[i].render(game_window);
        }

        game_window.update_screen();
        
        frame++;

        if (frame/8 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // if - animation frame reset
    } // while
} // Game::new_game