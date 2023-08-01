#include "game.h"

Game::Game() 
{
    player.set_player_name("Default");
    enemies = 0;
    active_enemies = 0;
    is_quit = true;
    player_died = false;
    victory = false;
} // default constructor

Game::Game(string player_name, Window window) 
{
    game_window = window;
    player.set_player_name(player_name);
    game_window.set_background_width(GAME_LEVEL_WIDTH);
    game_window.set_background_height(GAME_LEVEL_HEIGHT);
    enemies = 0;
    active_enemies = 0;
    is_quit = true;
    player_died = false;
    victory = false;
} // explicit constructor

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

void Game::set_background(string media_path)
{
    game_window.set_background(media_path);
} // Game::set_background

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

void Game::start_game(int enemy_number)
{
    // activates game - sets quit to false
    is_quit = false;

    // initiate game background internally - can be reset from interface scope
    set_background("assets/media/track.png");

    // initiate local variables for game running
    int frame = 0;
    int total_frames = 0;
    SDL_Event game_event;
    Timer step_timer;

    // initialize camera for scrolling
    Camera camera(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

    // initiates game play data
    enemies = enemy_number;
    active_enemies = enemy_number;
    player_died = false;
    victory = false;
    SDL_Texture* death_text = game_window.load_from_rendered_text(DEATH_MESSAGE, DEFAULT_FONT_COLOR);
    SDL_Texture* victory_text = game_window.load_from_rendered_text(VICTORY_MESSAGE, DEFAULT_FONT_COLOR);
    SDL_Rect center_target = CENTER_TEXT_TARGET;

    // initiate main character
    Dawg me(player.get_player_name(), 0, 0, game_window);
    Desk desk("desk", game_window);

    // initiate dawgs - dawgs are makeshift name for the most complex character type
    vector<Dawg*> dawgs(enemies); // these are enemy dawgs

    // randomize initial starting positions for enemies
    for (size_t i = 0; i < dawgs.size(); i++)
    {
        dawgs[i] = new Dawg("", GAME_LEVEL_WIDTH, GAME_LEVEL_HEIGHT, game_window);
        dawgs[i] -> set_x( 300 + rand() % (GAME_LEVEL_WIDTH - 300));
        dawgs[i] -> set_y(300 + rand() % (GAME_LEVEL_HEIGHT - 300));
    } // for - initializes enemy locations

    while(!is_quit) // game runs while quit is false
    {
        // MAIN GAME LOOP
        if (SDL_PollEvent(& game_event))
        {        
            // PROCESS EVENTS    
            if (game_event.type == SDL_QUIT)
            {
                is_quit = true;
            } // if - quit game
            else if (game_event.type == SDL_KEYDOWN)
            {
                switch (game_event.key.keysym.sym)
                {
                    // for keypress q and ESC, quits game
                    case SDLK_q:
                    is_quit = true;
                    break;

                    case SDLK_ESCAPE:
                    is_quit = true;
                    break;
                } // switch - process individual key event
            } // else if

            // using encapsulated functions to handle general player event for player with input
            me.handle_event(game_event);

        } // if - game event poll check
        
        // randomize dawg movement

        // every "change_rate" frames, the velocities for dawgs are randomly reset with 
        // dictated variance. The change rate also has randomized dictated variance for
        // artificial randomized behavior with control.

        int change_rate = (RATE_RAND_MID - rand() % RATE_RANT_RANGE);

        if (total_frames % change_rate == 0)
        {
            for (size_t i = 0; i < dawgs.size(); i++)
            {
                dawgs[i] -> set_vx(DAWG_RAND_SPEED_MID - double(rand() % DAWG_RAND_SPEED_RANGE));
                dawgs[i] -> set_vx(DAWG_RAND_SPEED_MID - double(rand() % DAWG_RAND_SPEED_RANGE));
            } // for 
        } // if 

        // GAME PLAY LOGIC

        // if player collides with desk, heal player
        if (has_collided(me, desk))
        {
            me.change_health(HEAL_AMOUNT);
            me.collision_rebound();
            
            // desk turns green upon impact
            if (desk.has_color_mod())
            {
                desk.modulate_color(0xFF, 0xFF, 0xFF);
            } // reset color;
            else
            {
                desk.modulate_color(0, 0xFF, 0xFF);
            } // set color
        } // if - collision

        // if player collides with enemy dawg, damage player
        for (size_t i = 0; i < dawgs.size(); i++)
        {
            if (dawgs[i] -> is_alive() && me.is_alive() && has_collided(me, *dawgs[i]))
            {
                me.change_health(-ENEMY_DAMAGE);
                dawgs[i] -> collision_rebound();
                me.collision_rebound(100);
            } // if - collision
        } // for - iterate over dawgs

        // player attack

        // player melee attack
        if (me.get_melee().is_active())
        {
            for (size_t i = 0; i < dawgs.size(); i++)
            {
                if (!dawgs[i] -> is_dead() && has_collided(me.get_melee(), *dawgs[i]))
                {
                    dawgs[i] -> collision_rebound();

                    HealthState state = dawgs[i] -> change_health(-2);
                    if (state == health_state_min)
                    {
                        active_enemies--;
                    } // if - killed, reduce enemies
                    me.reset_melee();
                } // if - melee collides
            } // for - iterate over dawgs
        } // if - melee is active - attack input detected
        
        // player projectile range attack
        for (size_t j = 0; j < me.get_projectiles().size(); j++)
        {
            Projectile pro = *me.get_projectiles()[j];

            for (size_t i = 0; i < dawgs.size(); i++)
            {
                if (pro.is_active() 
                && dawgs[i] -> is_alive()
                && has_collided(pro, *dawgs[i]))
                {
                    HealthState state = dawgs[i] -> change_health(-2);
                    if (state == health_state_min)
                    {
                        active_enemies--;
                    } // if - killed, reduce enemies
                    me.get_projectiles()[j] -> reset();
                } // if - projectile collides
            } // for - iterate over dawgs
        } // for - iterate over projectiles
        
        // PROCESS DEATH

        // only activates death spin animation if player is not already dead
        if (me.is_dead() && !player_died)
        {
            me.spin(90);
            player_died = true;
        } // if - player dies

        if (active_enemies == 0)
        {
            victory = true;
        } // if - VICTORY!!
        
        // PROCESS MOVEMENT ON SCREEN

        // enter time window
        double time_step = step_timer.get_seconds();

        // move player
        me.move(game_window, time_step);

        // move enemy dawgs
        for (size_t i = 0; i < dawgs.size(); i++)
        {
            if (dawgs[i]->is_alive())
            {
                dawgs[i] -> move(game_window, time_step);
            } // move if alive
        } // for - iterate over all dawgs

        step_timer.start(); // restart timer
        
        // exits time window

        // RENDER 

        // process camera for movement
        camera.process_camera(me.get_box(), GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GAME_LEVEL_WIDTH, GAME_LEVEL_HEIGHT);

        // reset window
        game_window.render_clear();

        // render background
        game_window.render_background(camera);

        // render player
        me.render(game_window, frame, camera);

        // render object
        desk.render(game_window, camera);

        // render enemies if alive
        for (size_t i = 0; i < dawgs.size(); i++)
        {
            if (dawgs[i]->is_alive())
            {
                dawgs[i] -> render(game_window, frame, camera);
            } // if - alvie
        } // for - iterate

        // END GAME MESSAGES

        if (player_died)
        {
            game_window.render(death_text, &center_target);
        } // if - death text

        if (victory)
        {
            game_window.render(victory_text, &center_target);
        } // if - victory text

        // update screen
        game_window.update_screen();
        
        // increment frame counts
        frame++; // increment frame
        total_frames++;
        
        // the game will have four frame animaiton speed, four frame animation too
        if (frame / 4 >= ANIMATION_FRAME_COUNT)
        {
            frame = 0; // reset frame count
        } // reset animation frame
    } // while

    for (size_t i = 0; i < dawgs.size(); i++)
    {
        delete dawgs[i];
    } // deallocate enemies
} // Game::start_game - the actual logic for the game goes here
