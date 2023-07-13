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
} // Game::start_game - the actual logic for the game goes here

void Game::TEST_TEMPLATE()
{
    bool isquit = false;

    game_window.set_background("assets/media/red_brick.png");
    int frame = 0;
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;

    while(!isquit)
    {
        // GAME LOOP
        if (SDL_PollEvent(& game_event))
        {        
            // PROCESS EVENTS    
            if (game_event.type == SDL_QUIT)
            {
                isquit = true;
            } // if - quit game
            else if (game_event.type == SDL_KEYDOWN)
            {
                switch (game_event.key.keysym.sym)
                {

                } // switch - process key event
            } // else if
        } // if - game event poll check
        
        // RENDER

        game_window.render_clear();
        game_window.render(game_window.get_background());
        game_window.update_screen();
        
        frame++; // increment frame

        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // reset animation frame
    } // while
} // Game::TEST_TEMPLATE

void Game::start_test_game_1()
{
    bool isquit = false;

    game_window.set_background("assets/media/red_brick.png");
    game_window.set_font("assets/fonts/font.ttf", 20, 0, 0xFF, 0xFF);
    game_window.set_local_text("sup fellas");
    int frame = 0;
    int x = 200;
    int y = 200;
    SDL_Rect target = {x, y, 100, 100};
    SDL_Rect text_target = {300, 300, 200, 200};
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;

    // initialize scancode key states
    const Uint8* current_key_states = SDL_GetKeyboardState(nullptr);

    Button buttons[4];
    // setting button positions
    buttons[0].set_position(0, 0);
    buttons[1].set_position(400,0);
    buttons[2].set_position(0,400);
    buttons[3].set_position(400,400);

    Music music;
    music.load_music("assets/music/music.wav");

    Audio effect;
    effect.load_audio("assets/audio/effect.wav");

    for (size_t i = 0; i < 4; i++)
    {
        buttons[i].set_texture(game_window, "assets/media/buttons.png");
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

                    case SDLK_q: // quit program
                    isquit = true;
                    break;

                } // switch

                
                if (current_key_states[SDL_SCANCODE_UP])
                {
                    y = y - 20;
                }           

                else if (current_key_states[SDL_SCANCODE_DOWN])
                
                {
                    y = y + 20;
                }

                else if (current_key_states[SDL_SCANCODE_RIGHT])
                {
                    flip = SDL_FLIP_HORIZONTAL;
                    x = x + 20;
                }    

                else if (current_key_states[SDL_SCANCODE_LEFT])
                {
                    flip = SDL_FLIP_NONE;
                    x = x - 20;
                }
            } // else if
            else // mouse event
            {
                for (size_t i = 0; i < 4; i++)
                {
                    buttons[i].handle_event(&game_event);
                }
            }

            // play audio based on mouse event
            if (buttons[0].get_state() == button_mouse_down)
            {
                music.play();
            }
            else if (buttons[0].get_state() == button_mouse_up)
            {
                music.pause();
            }
            else if (buttons[1].get_state() == button_mouse_down)
            {
                music.stop();
            }
            else if (buttons[2].get_state() == button_mouse_down)
            {
                effect.play();
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
} // Game::start_test_game_1

void Game::start_test_game_2()
{
    bool isquit = false;

    game_window.set_background("assets/media/red_brick.png");

    int frame = 0;
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;

    Timer timer;
    stringstream time_text;
    SDL_Texture* text = nullptr;
    timer.start();

    int counted_frames = 0;
    FPS_timer.start();


    while(!isquit)
    {
        // GAME LOOP
        
        // calculate frames per second

        FPS_AVG = counted_frames / (FPS_timer.get_ticks() / 1000.f);
        if (FPS_AVG > 200000)
        {
            FPS_AVG = 0;
        } // if - correct for boot error

        if (SDL_PollEvent(& game_event))
        {        
            // PROCESS EVENTS    
            if (game_event.type == SDL_QUIT)
            {
                isquit = true;
            } // if - quit game
            else if (game_event.type == SDL_KEYDOWN)
            {
                switch (game_event.key.keysym.sym)
                {
                    case SDLK_s:
                    timer.start();
                    break;

                    case SDLK_p:
                    timer.pause();
                    break;

                    case SDLK_u:
                    timer.unpause();
                    break;

                    case SDLK_k:
                    timer.stop();
                    break;
                } // switch - process key event
            } // else if
        } // if - game event poll check
        
        // get the time text
        SDL_Rect target = {0,0, 600, 200};
        SDL_Color color = {0, 0, 0};
        time_text.str(""); // initialize
        time_text << "Average Frames Per Second " << FPS_AVG; // get FPS
        text = game_window.load_from_rendered_text(time_text.str().c_str(), color);
        // RENDER

        game_window.render_clear();
        game_window.render(game_window.get_background());
        game_window.render(text, &target);
        game_window.update_screen();
        
        frame++; // increment frame for animation
        counted_frames++; // increment total global frame count for FPS calculation

        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // if - reset animation frame
    } // while
} // Game::start_test_game_2

