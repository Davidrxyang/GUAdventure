#include "game.h"

Game::Game() 
{
    player.set_player_name("Default");
    enemies = 0;
    active_enemies = 0;
    is_quit = true;
    is_paused = true;
    can_continue = false;
    player_died = false;
    victory = false;
    state = game_default;
    current_level = 0;

    dawg_speed_mid = DAWG_RAND_SPEED_MID;
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
    is_paused = true;
    can_continue = false;
    player_died = false;
    victory = false;
    state = game_default;
    current_level = 0;

    dawg_speed_mid = DAWG_RAND_SPEED_MID;
} // explicit constructor

void Game::set_enemy_speed(double speed)
{
    if (speed > 0)
    {
        dawg_speed_mid = speed;
    } // if - bounds checking
} // Game::set_enemy_speed

void Game::increase_enemy_speed(double speed)
{
    if (dawg_speed_mid + speed > 0)
    {
        dawg_speed_mid += speed;
    } // if - bounds checking
} // Game::increase_enemy_speed

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

void Game::handle_game_event(SDL_Event &e)
{
    if (e.type == SDL_QUIT)
    {
        is_quit = true;
        state = game_quit;
    } // if - quit
    else if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            // for keypress q and ESC, quits game
            case SDLK_q:
            is_quit = true;
            state = game_quit;
            break;
            case SDLK_ESCAPE:
            is_quit = true;
            state = game_quit;
            break;

            // p UNpauses game
            case SDLK_p:
            is_paused = !is_paused;
            break;

            // TODO - REMOVE THIS - TAB to skip level, for TESTING 
            case SDLK_TAB:
            victory = true;
            break;
        } // switch - process individual key event

        if (victory || player_died)
        {
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                can_continue = true;
            } // if - space bar - continue to next level
        } // if - only can change continue state when game ends
    } // else if
} // Game::handle_event

void Game::process_end_game()
{
    if (victory)
    {
        state = game_victory;
        is_paused = true;
    } // if - victory
    else if (player_died)
    {
        state = game_defeat;
        is_paused = true;
    } // if - defeat
    else 
    {
        state = game_default;
    } // else - state remains default
} // Game::process_end_game

void Game::render_data_panel(int current_health)
{
    // set game state display text first 
    string s_text = "";
    if (victory)
    {
        s_text = "Victory - Press [SPACE] to Continue or [Q] to Quit.";
    } // if - victory 
    else if (player_died)
    {
        s_text = "You Died - Press [SPACE] or [Q] to Quit Game.";
    } // else if - defeat
    else if (is_paused)
    {
        s_text = "Game Paused - Press [P] to Resume Game.";
    } // else if - paused
    else
    {
        s_text = "Game Active - Press [Q] to Quit, [P] to Pause.";
    } // else if - default

    SDL_Rect data_panel = DATA_PANEL;
    SDL_Texture* level_text = game_window.load_from_rendered_text("Level: " + to_string(current_level), DEFAULT_FONT_COLOR);
    SDL_Texture* total_enemies_text = game_window.load_from_rendered_text("Enemies: " + to_string(enemies), DEFAULT_FONT_COLOR);
    SDL_Texture* active_enemies_text = game_window.load_from_rendered_text("Remaining Enemies: " + to_string(active_enemies), DEFAULT_FONT_COLOR);
    SDL_Texture* health_text = game_window.load_from_rendered_text("Health: " + to_string(current_health), DEFAULT_FONT_COLOR);
    SDL_Texture* state_text = game_window.load_from_rendered_text(s_text, DEFAULT_FONT_COLOR);
    SDL_Texture* espeed_text = game_window.load_from_rendered_text("Enemy Speed: " + to_string(int(dawg_speed_mid)), DEFAULT_FONT_COLOR);
 
    SDL_Rect level_text_target = {DATA_PANEL_X + 10, DATA_PANEL_Y, 120, DATA_PANEL_HEIGHT / 2};
    SDL_Rect tenemies_text_target = {DATA_PANEL_WIDTH / 4, DATA_PANEL_Y, 120, DATA_PANEL_HEIGHT / 2};
    SDL_Rect aenemies_text_target = {DATA_PANEL_WIDTH / 2, DATA_PANEL_Y, 240, DATA_PANEL_HEIGHT / 2};
    SDL_Rect health_text_target = {DATA_PANEL_WIDTH - DATA_PANEL_WIDTH / 4, DATA_PANEL_Y, 120, DATA_PANEL_HEIGHT / 2};
    SDL_Rect state_text_target = {DATA_PANEL_X + 10, DATA_PANEL_Y + DATA_PANEL_HEIGHT / 2, 700, DATA_PANEL_HEIGHT / 2};
    SDL_Rect espeed_text_target = {DATA_PANEL_WIDTH - DATA_PANEL_WIDTH / 4, DATA_PANEL_Y + DATA_PANEL_HEIGHT / 2, 240, DATA_PANEL_HEIGHT / 2};

    game_window.render_rect(&data_panel, 0xFF, 0xFF, 0xFF);
    game_window.render(level_text, &level_text_target);
    game_window.render(total_enemies_text, &tenemies_text_target);
    game_window.render(active_enemies_text, &aenemies_text_target);     
    game_window.render(health_text, &health_text_target);     
    game_window.render(state_text, &state_text_target);     
    game_window.render(espeed_text, &espeed_text_target);
} // Game::render_data_panel

GameEndState Game::start_game(int enemy_number)
{
    // activates game - sets quit to false
    is_quit = false;
    is_paused = false;
    can_continue = false;

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
        while (!is_paused && !is_quit) // game runs while not paused
        {
            // MAIN GAME LOOP

            // randomize dawg movement

            // every "change_rate" frames, the velocities for dawgs are randomly reset with 
            // dictated variance. The change rate also has randomized dictated variance for
            // artificial randomized behavior with control.

            int change_rate = (RATE_RAND_MID - rand() % RATE_RANT_RANGE);

            if (total_frames % change_rate == 0)
            {
                for (size_t i = 0; i < dawgs.size(); i++)
                {
                    dawgs[i] -> set_vx(dawg_speed_mid - double(rand() % (2 * int(dawg_speed_mid))));
                    dawgs[i] -> set_vx(dawg_speed_mid - double(rand() % (2 * int(dawg_speed_mid))));
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

            // render data panel
            render_data_panel(me.get_health());

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

            // PROCESS END GAME
            
            process_end_game();

            // PROCESS NEW EVENTS, incl GAME QUIT/GAME PAUSE

            if (SDL_PollEvent(& game_event))
            {        
                // PROCESS EVENTS    
                handle_game_event(game_event);
                me.handle_event(game_event);
                if (is_paused)
                {
                    me.stop();
                    
                    // one - off render data panel to show paused message
                    render_data_panel(me.get_health());
                    game_window.update_screen();
                } // if - stop me and render pause
            } // if - game event poll check
        } // while - PAUSE

        // PAUSED GAME FUNCTIONS

        // during pause, poll for unpause event or quit, if game did not finish
        if (SDL_PollEvent(& game_event))
        {        
            handle_game_event(game_event);
        } // if - game event poll

        // if game ended, no unpausing allowed
        if (victory || player_died)
        {
            is_paused = true;

            if (can_continue)
            {
                is_quit = true;
            } // if - can continue, quits
        } // if 
    } // while - QUIT

    for (size_t i = 0; i < dawgs.size(); i++)
    {
        delete dawgs[i];
    } // deallocate enemies

    return state;
} // Game::start_game - the actual logic for the game goes here
