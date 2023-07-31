#include "game.h"

Game::Game() 
{
    // calls class default constructors
} // default constructor

Game::Game(string player_name) 
: game_window("Game", 0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)
{
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

bool Game::has_collided(SDL_Rect a, SDL_Rect b) const
{
    // a COLLIDES WITH b    
    int left_a = a.x;
    int right_a = left_a + a.w;
    int top_a = a.y;
    int bottom_a = top_a + a.h;

    int left_b = b.x;
    int right_b = left_b + b.w;
    int top_b = b.y;
    int bottom_b = top_b + b.h;

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

bool Game::has_collided(double x, double y, Entity b) const
{
    int left_b = b.get_box().x;
    int right_b = left_b + b.get_box().w;
    int top_b = b.get_box().y;
    int bottom_b = top_b + b.get_box().h;

    if (x >= left_b && x <= right_b
    && y >= top_b && y <= bottom_b)
    {
        return true;
    } // if - collides
    return false;
} // Game::has_collided

void Game::start_test_game_6()
{
    bool isquit = false;

    game_window.set_background("assets/media/track.png");

    int frame = 0;
    int total_frames = 0;
    SDL_Event game_event;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    Timer step_timer;

    Dog me("me", game_window);
    Desk desk("desk", game_window);

    /*
    Dog dog1("dog1", game_window);
    Dog dog2("dog2", game_window);
    Dog dog3("dog3", game_window);

    dog1.set_x(GAME_LEVEL_WIDTH - 300);
    dog1.set_y(300);
    dog2.set_x(300);
    dog2.set_y(GAME_LEVEL_HEIGHT - 300);
    dog3.set_x(GAME_LEVEL_WIDTH - 300);
    dog3.set_y(GAME_LEVEL_HEIGHT - 300);
    */

    vector<Dog*> dogs(30);

    for (size_t i = 0; i < dogs.size(); i++)
    {
        dogs[i] = new Dog("", game_window);
        dogs[i] -> set_x( 300 + rand() % (GAME_LEVEL_WIDTH - 300));
        dogs[i] -> set_y(300 + rand() % (GAME_LEVEL_HEIGHT - 300));
    }

    /*
    dogs.push_back(&dog1);
    dogs.push_back(&dog2);
    dogs.push_back(&dog3);
    */


    // TESTING CAMERA SCROLLING

    Camera camera(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
 
    // just to make sure player died
    bool has_spun = false;

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

                } // switch - process individual key event
            }

             me.handle_event(game_event);
        } // if - game event poll check
        
        if (has_collided(me, desk))
        {
            me.change_health(3);
            me.collision_rebound();
            desk.orient(me.get_direction());
        } // if - collision

        // randomize dog movement

        int change_rate = (100 - rand()%30);
        if (total_frames % change_rate == 0)
        {
            for (size_t i = 0; i < dogs.size(); i++)
            {
                dogs[i] -> set_vx(200 - rand()%400);
                dogs[i] -> set_vx(200 - rand()%400);
            }
        }

        /*
        for (size_t i = 0; i < dogs.size(); i++)
        {
            Dog d = *dogs[i];
            if (has_collided(me.get_box(), dogs[i] -> get_box()))
            {
                me.collision_rebound();
                dogs[i] -> collision_rebound();
                me.change_health(-1);
            }
        }
        */

        if (me.get_melee().is_active())
        {
            for (size_t i = 0; i < dogs.size(); i++)
            {
                if (!dogs[i] -> is_dead() && has_collided(me.get_melee(), *dogs[i]))
                {
                    dogs[i] -> collision_rebound();
                    //me.collision_rebound(100);
                    //me.change_health(-1);
                    me.reset_melee();
                    dogs[i] -> change_health(-2);
                }
            }
        }
        
        for (size_t j = 0; j < me.get_projectiles().size(); j++)
        {
            Projectile pro = *me.get_projectiles()[j];

            for (size_t i = 0; i < dogs.size(); i++)
            {
                if (pro.is_active() 
                && dogs[i] -> is_alive()
                && has_collided(pro, *dogs[i]))
                {
                    dogs[i] -> change_health(-2);
                    me.get_projectiles()[j] -> reset();
                }
            }
        } // process all projectiles in array
        
        

        // PROCESS ENTITIES
        double time_step = step_timer.get_seconds();

        me.move(game_window, time_step);

        for (size_t i = 0; i < dogs.size(); i++)
        {
            dogs[i] -> move(game_window, time_step);
            if (dogs[i] -> is_dead())
            {
                dogs[i] -> spin(30);
            }
        }

        step_timer.start(); // restart timer

        if (me.is_dead() && !has_spun)
        {
            me.spin(90);
            cout << "You died..." << endl;
            has_spun = true;
        } // if - player dies


        // RENDER

        camera.process_camera(me.get_box(), GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GAME_LEVEL_WIDTH, GAME_LEVEL_HEIGHT);

        game_window.render_clear();
        game_window.render_background(camera);

        me.render(game_window, frame, camera);
        desk.render(game_window, camera);

        for (size_t i = 0; i < dogs.size(); i++)
        {
            dogs[i] -> render(game_window, frame, camera);
        }

        game_window.update_screen();
        
        frame++; // increment frame
        total_frames++;

        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // reset animation frame
    } // while

    for (size_t i = 0; i < dogs.size(); i++)
    {
        delete dogs[i];
    } // deallocate

} // Game::start_test_game_6
