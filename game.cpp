#include "game.h"

Game::Game() 
{
    // calls class default constructors
} // default constructor

Game::Game(string player_name) 
: game_window("Game", 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)
{
    this -> jack = Dog("jack", game_window);
    player.set_player_name(player_name);

    game_window.set_background_width(GAME_LEVEL_WIDTH);
    game_window.set_background_height(GAME_LEVEL_HEIGHT);
} // explicit constructor

void Game::start_game()
{
    bool isquit = false;
} // Game::start_game - the actual logic for the game goes here

bool Game::has_collided(Entity a, Entity b) const
{
    // a COLLIDES WITH b    
    int left_a = a.get_box().x;
    int right_a = left_a + a.get_box().w;
    int top_a = a.get_box().y;
    int bottom_a = top_a + a.get_box().h;

    int left_b = b.get_box().x;
    int right_b = left_b + b.get_box().w;
    int top_b = b.get_box().y;
    int bottom_b = top_b + b.get_box().h;

    // collision logic
    if (bottom_a <= top_b)
    {
        return false;
    } // if
    if (top_a >= bottom_b)
    {
        return false;
    } // if
    if (right_a <= left_b)
    {
        return false;
    } // if
    if (left_a >= right_b)
    {
        return false;
    } // if
    return true; // if none satisfy condition, the boxes do not overlap, return true
} // Game::has_collided

/*

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
            jack.handle_event(game_event);
        } // if - game event poll check
        
        // PROCESS ENTITIES

        jack.move(game_window);

        // RENDER

        game_window.render_clear();
        game_window.render(game_window.get_background());
        jack.render_dog(game_window, frame);

        jack.render_box(game_window);
        
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

        if (frame/4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // if - animation frame reset
    } // while
} // Game::start_test_game_1

void Game::start_test_game_2()
{
    bool isquit = false;

    game_window.set_background("assets/media/track.png");

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

        FPS_AVG = counted_frames / FPS_timer.get_seconds();
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

                } // switch - process key event
                jack.handle_event(game_event);
            } // else if
        } // if - game event poll check
        
        // get the time text
        SDL_Rect target = {0,0, 600, 200};
        SDL_Color color = {0, 0, 0};
        time_text.str(""); // initialize
        time_text << "Average Frames Per Second " << FPS_AVG; // get FPS
        text = game_window.load_from_rendered_text(time_text.str().c_str(), color);
        
        // PROCESS CHARACTER ENTITIES
        jack.move(game_window);
        // RENDER

        game_window.render_clear();
        game_window.render(game_window.get_background());
        game_window.render(text, &target);
        jack.render(game_window, frame); // render jack
        jack.render_box(game_window); // render jack's collision box
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

void Game::start_test_game_3()
{
    bool isquit = false;

    game_window.set_background("assets/media/track.png");

    int frame = 0;
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    Desk desk("desk", game_window);
    // Camera camera(0, 0, 500, 500);

    // testing text input
    Text text("text", game_window, DEFAULT_BLACK);

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
            jack.handle_event(game_event);
            text.handle_text_event(game_event);
        } // if - game event poll check
        
        // PROCESS ENTITIES

        jack.move(game_window);
        text.move(game_window);

        if (has_collided(jack, desk))
        {
            jack.stop();
            jack.set_x(0);
            jack.set_y(0);
            jack.spin(180);
        } // if - collision

        if (has_collided(text, desk))
        {
            text.clear();
            text.stop();
        } //if - collision

        // RENDER

        game_window.render_clear();
        game_window.render(game_window.get_background());
        jack.render(game_window, frame); // render jack
        desk.render(game_window);
        text.render_text(game_window);

        jack.render_box(game_window);
        desk.render_box(game_window);
        text.render_box(game_window);

        game_window.update_screen();
        
        frame++; // increment frame for animation

        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // if - reset animation frame
    } // while
} // Game::start_test_game_3

void Game::start_test_game_4()
{
    bool isquit = false;

    game_window.set_background("assets/media/red_brick.png");
    int frame = 0;
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;

    //testing data entry and storage
    Sint32 data[10];
    SDL_RWops* file = SDL_RWFromFile("data/file.bin", "r+b"); // path, r+b is read binary

    if (file == nullptr)
    {
        cout << "Failed to open file: " << SDL_GetError() << endl;
        // no file, so create file 
        file = SDL_RWFromFile("data/file.bin", "w+b"); // write binary
        if (file != nullptr)
        {
            cout << "new file created" << endl;
            for (size_t i = 0; i < 10; i++)
            {
                // initialize data 
                data[i] = i;
                SDL_RWwrite(file, &data[i], sizeof(Sint32), 1);
            } // initialize file
            // close file
            SDL_RWclose(file);
        }
        else 
        {
            cout << "failed to create file: " << SDL_GetError() << endl;
        } // else - failed to create file
    } // if - empty file
    else 
    {
        cout << "Reading file." << endl;
        for (size_t i = 0; i < 10; i++)
        {
            SDL_RWread(file, &data[i], sizeof(Sint32), 1);
            // read from file into data array, the file should have all zeros
        } // for - read file
        SDL_RWclose(file);
    } // else - file exists

    // TODO ADD CLEAN FILE FUNCTIONALITY IN QUIT FUNCTION


    string text = " ";
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
                    case SDLK_0:
                    text = to_string(data[0]);
                    break;

                    case SDLK_1:
                    text = to_string(data[1]);
                    break;
                    
                    case SDLK_2:
                    text = to_string(data[2]);
                    break;

                    case SDLK_3:
                    text = to_string(data[3]);
                    break;
                } // switch - process key event
            } // else if
        } // if - game event poll check
        
        // RENDER

        SDL_Texture* text_texture = game_window.load_from_rendered_text(text, DEFAULT_BLACK);
        game_window.render_clear();
        game_window.render(game_window.get_background());
        game_window.render(text_texture);
        game_window.update_screen();
        
        frame++; // increment frame

        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // reset animation frame
    } // while
} // Game::start_test_game_4

void Game::start_test_game_5()
{
    bool isquit = false;

    game_window.set_background("assets/media/track.png");

    int frame = 0;
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    Desk desk("desk", game_window);
    // Camera camera(0, 0, 500, 500);

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
            jack.handle_event(game_event);
        } // if - game event poll check
        
        // PROCESS ENTITIES

        jack.move(game_window);

        if (has_collided(jack, desk))
        {
            jack.stop();
            jack.set_x(0);
            jack.set_y(0);
            jack.spin(180);
        } // if - collision

        // RENDER

        game_window.render_clear();
        game_window.render(game_window.get_background());
        jack.render_dog(game_window, frame); // render jack
        desk.render(game_window);

        jack.render_box(game_window);
        desk.render_box(game_window);

        game_window.update_screen();
        
        frame++; // increment frame for animation

        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // if - reset animation frame
    } // while
} // Game::start_test_game_5

*/

void Game::start_test_game_6()
{
    bool isquit = false;

    game_window.set_background("assets/media/track.png");

    int frame = 0;
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    Timer step_timer;

    // TESTING CAMERA SCROLLING

    Camera camera(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
 

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
            jack.handle_event(game_event);
        } // if - game event poll check
        
        // PROCESS ENTITIES
        double time_step = step_timer.get_seconds();
        jack.move(game_window, time_step);

        step_timer.start(); // restart timer

        // PROCESS CAMERA

        camera.set_x((jack.get_x() + jack.get_w() / 2) - GAME_SCREEN_WIDTH / 2);
        camera.set_y((jack.get_y() + jack.get_h() / 2) - GAME_SCREEN_HEIGHT / 2);

        // camera bounds checking
        if (camera.get_x() < 0)
        {camera.set_x(0);}
        if (camera.get_y() < 0)
        {camera.set_y(0);}
        if (camera.get_x() > GAME_LEVEL_WIDTH - camera.get_w())
        {camera.set_x(GAME_LEVEL_WIDTH - camera.get_w());}
        if (camera.get_y() > GAME_LEVEL_HEIGHT - camera.get_h())
        {camera.set_y(GAME_LEVEL_HEIGHT - camera.get_h());} 
        
        // RENDER

        game_window.render_clear();
        game_window.render_background(camera);

        jack.render_dog(game_window, frame, camera);
        jack.render_box(game_window, camera);

        game_window.update_screen();
        
        frame++; // increment frame

        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // reset animation frame
    } // while
} // Game::start_test_game_6
