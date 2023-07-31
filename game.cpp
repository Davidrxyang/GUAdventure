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
    Dog dog1("dog1", game_window);
    Dog dog2("dog2", game_window);
    Dog dog3("dog3", game_window);

    dog1.set_x(GAME_LEVEL_WIDTH - 300);
    dog1.set_y(300);
    dog2.set_x(300);
    dog2.set_y(GAME_LEVEL_HEIGHT - 300);
    dog3.set_x(GAME_LEVEL_WIDTH - 300);
    dog3.set_y(GAME_LEVEL_HEIGHT - 300);

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
            dog1.set_vx(200 - rand()%400);
            dog2.set_vx(200 - rand()%400);
            dog3.set_vx(200 - rand()%400);
            dog1.set_vy(200 - rand()%400);
            dog2.set_vy(200 - rand()%400);
            dog3.set_vy(200 - rand()%400);
        }

        if (me.get_melee().is_active())
        {
            if (!dog1.is_dead() && has_collided(me.get_melee(), dog1))
            {
                dog1.collision_rebound();
                //me.collision_rebound(100);
                //me.change_health(-1);
                me.reset_melee();
                dog1.change_health(-2);
            }
            if (!dog2.is_dead() && has_collided(me.get_melee(), dog2))
            {
                dog2.collision_rebound();
                //me.collision_rebound(100);
                //me.change_health(-1);
                me.reset_melee();
                dog2.change_health(-2);
            }
            if (!dog3.is_dead() && has_collided(me.get_melee(), dog3))
            {
                dog3.collision_rebound();
                //me.collision_rebound(100);
                //me.change_health(-1);
                me.reset_melee();
                dog3.change_health(-2);
            }
        }
        
        for (size_t i = 0; i < me.get_projectiles().size(); i++)
        {
            Projectile pro = *me.get_projectiles()[i];

            if (pro.is_active() 
            && dog1.is_alive()
            && has_collided(pro, dog1))
            {
                dog1.change_health(-2);
                me.get_projectiles()[i] -> reset();
            }
            if (pro.is_active() 
            && dog2.is_alive()
            && has_collided(pro, dog2))
            {
                dog2.change_health(-2);
                me.get_projectiles()[i] -> reset();
            }
            if (pro.is_active() 
            && dog3.is_alive()
            && has_collided(pro, dog3))
            {
                dog3.change_health(-2);
                me.get_projectiles()[i] -> reset();
            }
        } // process all projectiles in array
        
        

        // PROCESS ENTITIES
        double time_step = step_timer.get_seconds();

        me.move(game_window, time_step);
        dog1.move(game_window, time_step);
        dog2.move(game_window, time_step);
        dog3.move(game_window, time_step);

        if (dog1.is_dead())
        {
            dog1.spin(30);
        }
        if (dog2.is_dead())
        {   
            dog2.spin(30);
        }
        if (dog3.is_dead())
        {
            dog3.spin(20);
        }
        
        step_timer.start(); // restart timer

        if (me.is_dead() && !has_spun)
        {
            me.spin(90);
            cout << "You died..." << endl;
            has_spun = true;
        } // if - player dies

        // PROCESS CAMERA
        process_camera(camera, me);
        camera.set_x((me.get_x() + me.get_w() / 2) - GAME_SCREEN_WIDTH / 2);
        camera.set_y((me.get_y() + me.get_h() / 2) - GAME_SCREEN_HEIGHT / 2);

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

        me.render(game_window, frame, camera);
        desk.render(game_window, camera);

        dog1.render(game_window, frame, camera);        
        dog2.render(game_window, frame, camera);        
        dog3.render(game_window, frame, camera);   

        game_window.update_screen();
        
        frame++; // increment frame
        total_frames++;

        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= animation_frame_count)
        {
            frame = 0; // reset frame count
        } // reset animation frame
    } // while
} // Game::start_test_game_6
