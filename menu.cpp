#include "menu.h"

Menu::Menu()
{
    is_quit = true;
    player_name = "";
    current_file = 0;
    // calls default constructors
} // Default Constructor

Menu::Menu(Player* player, Window window)
{
    if (save_1.empty("assets/data/s1.txt"))
    {
        save_1.write("assets/data/s1.txt");
    } // if - empty
    else
    {
        save_1.read("assets/data/s1.txt");
    } // else - not empty, read 
    if (save_2.empty("assets/data/s2.txt"))
    {
        save_2.write("assets/data/s2.txt");
    } // if - empty
    else
    {
        save_2.read("assets/data/s2.txt");
    } // else - not empty, read 
    if (save_3.empty("assets/data/s3.txt"))
    {
        save_3.write("assets/data/s3.txt");
    } // if - empty
    else
    {
        save_3.read("assets/data/s3.txt");
    } // else - not empty, read 
    if (save_4.empty("assets/data/s4.txt"))
    {
        save_4.write("assets/data/s4.txt");
    } // if - empty
    else
    {
        save_4.read("assets/data/s4.txt");
    } // else - not empty, read 
    if (save_5.empty("assets/data/s5.txt"))
    {
        save_5.write("assets/data/s5.txt");
    } // if - empty
    else
    {
        save_5.read("assets/data/s5.txt");
    } // else - not empty, read 

    is_quit = true;
    menu_window = window;
    player_name = "";
    this -> player = player;
    current_file = 0;
} // explicit constructor

MenuExitState Menu::start_menu()
{
    is_quit = false;
    int frame = 0;
    SDL_Event menu_event;
    menu_window.set_background("assets/media/background/menu.png");
    // load initial function - select game
    function = menu_select_game;
    
    while (!is_quit)
    {   
        initialize();

        // MENU MAIN LOOP

        // RENDER

        menu_window.render_clear();
        menu_window.render_background();
        render_title();

        // render current function
        switch(function)
        {
            case menu_select_game:
            render_select_game();
            break;

            case menu_enter_player_name:
            render_enter_player_name();
            break;

            case menu_select_type:
            render_select_type();
            break;

            case menu_delete_save:
            render_delete_save();
            break;

            case menu_admin_pwd:
            render_admin_pwd();
            break;

            case menu_complete:
            render_complete();
            break;

            default:
            break;
        } // switch - render based on current function

        menu_window.update_screen();

        // handle event
        if (poll_event(&menu_event))
        {
            if (menu_event.type == SDL_QUIT)
            {
                is_quit = true;
                return menu_quit;
            } // if - quit

            switch(function)
            {
                case menu_select_game:
                select_game(menu_event);
                break;

                case menu_enter_player_name:
                enter_player_name(menu_event);
                break;

                case menu_select_type:
                select_player_type(menu_event);
                break;

                case menu_delete_save:
                delete_save(menu_event);
                break;

                case menu_admin_pwd:
                admin_pwd(menu_event);
                break;

                case menu_complete:
                complete(menu_event);
                break;

                default:
                break;
            } // switch - current menu function
        } // if - poll event
    } // while - runs while not quit

    // exit success
    return menu_exit_success;
} // Menu::start_menu

GameFile Menu::get_current_file() const
{
    switch (current_file)
    {
        case 1:
        return save_1;
        break;

        case 2:
        return save_2;
        break;

        case 3:
        return save_3;
        break;

        case 4:
        return save_4;
        break;

        case 5:
        return save_5;
        break;

        default:
        return save_1;
        break;
    } // switch - return file
} // Menu::get_current_file

int Menu::poll_event(SDL_Event* e)
{
    return SDL_PollEvent(e);
} // Game::poll_event

void Menu::initialize()
{
    // initialize text input
    SDL_StartTextInput();
} // Menu::initialize

void Menu::select_game(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_1:
            current_file = 1;
            if (!save_1.empty("assets/data/s1.txt"))
            {
                set_player(save_1);
                function = menu_complete;
            } // if - empty
            else
            {
                function = menu_enter_player_name;
            } // else - if empty, start new game
            break;

            case SDLK_2:
            current_file = 2;
            if (!save_2.empty("assets/data/s2.txt"))
            {
                set_player(save_2);
                function = menu_complete;
            } // if - empty
            else
            {
                function = menu_enter_player_name;
            } // else - if empty, start new game
            break;

            case SDLK_3:
            current_file = 3;
            if (!save_3.empty("assets/data/s3.txt"))
            {
                set_player(save_3);
                function = menu_complete;
            } // if - empty
            else
            {
                function = menu_enter_player_name;
            } // else - if empty, start new game
            break;

            case SDLK_4:
            current_file = 4;
            if (!save_4.empty("assets/data/s4.txt"))
            {
                set_player(save_4);
                function = menu_complete;
            } // if - empty
            else
            {
                function = menu_enter_player_name;
            } // else - if empty, start new game
            break;

            case SDLK_5:
            current_file = 5;
            if (!save_5.empty("assets/data/s5.txt"))
            {
                set_player(save_5);
                function = menu_complete;
            } // if - empty
            else
            {
                function = menu_enter_player_name;
            } // else - if empty, start new game
            break;

            case SDLK_d:
            function = menu_delete_save;
            break;
    
            default:
            break;
        } // switch - basic KEYDOWN handling
    } // if - keydown
}// Menu::select_game

void Menu::enter_player_name(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_RETURN:
            if (player_name == "")
            {
                player_name = " ";
            } // if - empty, add space for rendering purposes
            player -> set_player_name(player_name);
            // advance to next function
            if (player_name == "AdminDavid")
            {
                function = menu_admin_pwd;
            } // if - pwd check
            else
            {
                function = menu_select_type;
            } // else - no admin
            break;

            // handle backspace
            case SDLK_BACKSPACE:
            if (player_name.length() > 0)
            {
                player_name.pop_back();
            } // if - backspace
            break;

            case SDLK_ESCAPE:
            function = menu_select_game;
            break;
    
            default:
            break;
        } // switch - basic KEYDOWN handling
    } // else if - keydown
    else if (e.type == SDL_TEXTINPUT)
    {
        if (player_name.length() < MAX_PLAYER_NAME_LENGTH)
        {
            player_name += e.text.text;
        } // if - name length bounds checking
    } // if - text input
} // Menu::enter_player_name

void Menu::select_player_type(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_m:
            player -> set_mode(melee);
            new_game();
            function = menu_complete;
            break;

            case SDLK_p:
            player -> set_mode(projectile);
            new_game();
            function = menu_complete;
            break;

            case SDLK_h:
            player -> set_mode(hybrid);
            new_game();
            function = menu_complete;
            break;

            case SDLK_ESCAPE:
            function = menu_enter_player_name;
            break;

            default:
            break;
        } // switch - mode
    } // if - keydown
} // Menu::select_player_type

void Menu::delete_save(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_1:
            current_file = 1;
            save_1.write("assets/data/s1.txt");
            function = menu_select_game;
            break;

            case SDLK_2:
            current_file = 2;
            save_2.write("assets/data/s2.txt");
            function = menu_select_game;
            break;

            case SDLK_3:
            current_file = 3;
            save_3.write("assets/data/s3.txt");
            function = menu_select_game;
            break;

            case SDLK_4:
            current_file = 4;
            save_4.write("assets/data/s4.txt");
            function = menu_select_game;
            break;

            case SDLK_5:
            current_file = 5;
            save_5.write("assets/data/s5.txt");
            function = menu_select_game;
            break;

            case SDLK_a:
            save_1.write("assets/data/s1.txt");
            save_2.write("assets/data/s2.txt");
            save_3.write("assets/data/s3.txt");
            save_4.write("assets/data/s4.txt");
            save_5.write("assets/data/s5.txt");
            function = menu_select_game;
            break;
    
            default:
            break;
        } // switch - basic KEYDOWN handling
    } // if - keydown
} // Menu::delete_save

void Menu::admin_pwd(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_RETURN:
            if (pwd == "")
            {
                pwd = " ";
            } // if - empty, add space for rendering purposes
            if (pwd == ADMIN_PWD)
            {
                player -> set_mode(admin);
                function = menu_complete;
            } // if - correct
            else
            {
                function = menu_select_game;
            } // else - incorrect
            break;

            // handle backspace
            case SDLK_BACKSPACE:
            if (player_name.length() > 0)
            {
                pwd.pop_back();
            } // if - backspace
            break;

            case SDLK_ESCAPE:
            function = menu_select_game;
            break;
    
            default:
            break;
        } // switch - basic KEYDOWN handling
    } // else if - keydown
    else if (e.type == SDL_TEXTINPUT)
    {
        if (pwd.length() < 5)
        {
            pwd += e.text.text;
        } // if - name length bounds checking
    } // if - text input
} // Menu::admin_pwd

void Menu::complete(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_RETURN)
        {
            is_quit = true;
        } // if - return starts game
    } // if - keydown
} // Menu::complete

void Menu::set_player(GameFile save)
{
    player -> set_player_name(save.get_name());
    player -> set_mode(save.get_player_mode());
    player -> set_score(save.get_current_score());
    player -> set_level(save.get_current_level());
    player -> set_remaining_enemies(save.get_remaining_enemies());
    player -> set_health(save.get_health());
    player -> set_x(save.get_x());
    player -> set_y(save.get_y());
} // Menu::set_player

void Menu::new_game()
{
    switch(current_file)
    {
        case 1:
        save_1.write("assets/data/s1.txt", player -> get_player_name(), player -> get_mode(), 
        player -> get_level(), player -> get_score(), player -> get_remaining_enemies(), player -> get_health(), player -> get_x(), player -> get_y());
        break;

        case 2:
        save_2.write("assets/data/s2.txt", player -> get_player_name(), player -> get_mode(), 
        player -> get_level(), player -> get_score(), player -> get_remaining_enemies(), player -> get_health(), player -> get_x(), player -> get_y());
        break;

        case 3:
        save_3.write("assets/data/s3.txt", player -> get_player_name(), player -> get_mode(), 
        player -> get_level(), player -> get_score(), player -> get_remaining_enemies(), player -> get_health(), player -> get_x(), player -> get_y());
        break;

        case 4:
        save_4.write("assets/data/s4.txt", player -> get_player_name(), player -> get_mode(), 
        player -> get_level(), player -> get_score(), player -> get_remaining_enemies(), player -> get_health(), player -> get_x(), player -> get_y());
        break;

        case 5:
        save_5.write("assets/data/s5.txt", player -> get_player_name(), player -> get_mode(), 
        player -> get_level(), player -> get_score(), player -> get_remaining_enemies(), player -> get_health(), player -> get_x(), player -> get_y());
        break;

        default:
        break;
    } // switch - write file
} // Menu::new_game

void Menu::render_title()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("MENU", DEFAULT_WHITE);
    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, 10, 400, 100};
    menu_window.render(text, &text_target);
} // Menu::render_title

void Menu::render_select_game()
{
    // set game text
    string g1 = "[1]";
    string g2 = "[2]";
    string g3 = "[3]";
    string g4 = "[4]";
    string g5 = "[5]";

    if (save_1.empty("assets/data/s1.txt"))
    {
        g1 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g1 = g1 + " | " + save_1.get_name() + " | Type: " + mode_to_text(save_1.get_player_mode())
        + " | Level: " + to_string(save_1.get_current_level()) + " | Score: " + to_string(save_1.get_current_score()) + " |";
    } // else - load text 
    if (save_2.empty("assets/data/s2.txt"))
    {
        g2 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g2 = g2 + " | " + save_2.get_name() + " | Type: " + mode_to_text(save_2.get_player_mode())
        + " | Level: " + to_string(save_2.get_current_level()) + " | Score: " + to_string(save_2.get_current_score()) + " |";
    } // else - load text 
    if (save_3.empty("assets/data/s3.txt"))
    {
        g3 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g3 = g3 + " | " + save_3.get_name() + " | Type: " + mode_to_text(save_3.get_player_mode())
        + " | Level: " + to_string(save_3.get_current_level()) + " | Score: " + to_string(save_3.get_current_score()) + " |";
    } // else - load text 
    if (save_4.empty("assets/data/s4.txt"))
    {
        g4 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g4 = g4 + " | " + save_4.get_name() + " | Type: " + mode_to_text(save_4.get_player_mode())
        + " | Level: " + to_string(save_4.get_current_level()) + " | Score: " + to_string(save_4.get_current_score()) + " |";
    } // else - load text 
    if (save_5.empty("assets/data/s5.txt"))
    {
        g5 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g5 = g5 + " | " + save_1.get_name() + " | Type: " + mode_to_text(save_5.get_player_mode())
        + " | Level: " + to_string(save_5.get_current_level()) + " | Score: " + to_string(save_5.get_current_score()) + " |";
    } // else - load text 

    SDL_Texture* text = menu_window.load_from_rendered_text("Select Game", DEFAULT_WHITE);
    SDL_Texture* delete_text = menu_window.load_from_rendered_text("Press [D] to delete select game", DEFAULT_WHITE);
    SDL_Texture* game1 = menu_window.load_from_rendered_text(g1, DEFAULT_WHITE);
    SDL_Texture* game2 = menu_window.load_from_rendered_text(g2, DEFAULT_WHITE);
    SDL_Texture* game3 = menu_window.load_from_rendered_text(g3, DEFAULT_WHITE);
    SDL_Texture* game4 = menu_window.load_from_rendered_text(g4, DEFAULT_WHITE);
    SDL_Texture* game5 = menu_window.load_from_rendered_text(g5, DEFAULT_WHITE);


    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, 120, 400, 100};
    SDL_Rect delete_text_target = {GAME_SCREEN_WIDTH / 2 - 250, 600, 500, 40};
    SDL_Rect g1_target = {GAME_SCREEN_WIDTH / 2 - 400, 300, 800, 50};
    SDL_Rect g2_target = {GAME_SCREEN_WIDTH / 2 - 400, 350, 800, 50};
    SDL_Rect g3_target = {GAME_SCREEN_WIDTH / 2 - 400, 400, 800, 50};
    SDL_Rect g4_target = {GAME_SCREEN_WIDTH / 2 - 400, 450, 800, 50};
    SDL_Rect g5_target = {GAME_SCREEN_WIDTH / 2 - 400, 500, 800, 50};

    SDL_Rect game_background = {GAME_SCREEN_WIDTH / 2 - 450, 280, 900, 300};

    menu_window.render_rect(&game_background, 0x74, 0x6B, 0x5A);
    menu_window.render(text, &text_target);
    menu_window.render(delete_text, &delete_text_target);
    menu_window.render(game1, &g1_target);
    menu_window.render(game2, &g2_target);
    menu_window.render(game3, &g3_target);
    menu_window.render(game4, &g4_target);
    menu_window.render(game5, &g5_target);

} // Menu::render_select_game

void Menu::render_delete_save()
{
    // set game text
    string g1 = "[1]";
    string g2 = "[2]";
    string g3 = "[3]";
    string g4 = "[4]";
    string g5 = "[5]";

    if (save_1.empty("assets/data/s1.txt"))
    {
        g1 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g1 = g1 + " | " + save_1.get_name() + " | Type: " + mode_to_text(save_1.get_player_mode())
        + " | Level: " + to_string(save_1.get_current_score()) + " | Score: " + to_string(save_1.get_current_level()) + " |";
    } // else - load text 
    if (save_2.empty("assets/data/s2.txt"))
    {
        g2 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g2 = g2 + " | " + save_2.get_name() + " | Type: " + mode_to_text(save_2.get_player_mode())
        + " | Level: " + to_string(save_2.get_current_score()) + " | Score: " + to_string(save_2.get_current_level()) + " |";
    } // else - load text 
    if (save_3.empty("assets/data/s3.txt"))
    {
        g3 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g3 = g3 + " | " + save_3.get_name() + " | Type: " + mode_to_text(save_3.get_player_mode())
        + " | Level: " + to_string(save_3.get_current_score()) + " | Score: " + to_string(save_3.get_current_level()) + " |";
    } // else - load text 
    if (save_4.empty("assets/data/s4.txt"))
    {
        g4 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g4 = g4 + " | " + save_4.get_name() + " | Type: " + mode_to_text(save_4.get_player_mode())
        + " | Level: " + to_string(save_4.get_current_score()) + " | Score: " + to_string(save_4.get_current_level()) + " |";
    } // else - load text 
    if (save_5.empty("assets/data/s5.txt"))
    {
        g5 += " EMPTY - Select to start new game ... ";
    } // if - empty
    else 
    {
        g5 = g5 + " | " + save_1.get_name() + " | Type: " + mode_to_text(save_5.get_player_mode())
        + " | Level: " + to_string(save_5.get_current_score()) + " | Score: " + to_string(save_5.get_current_level()) + " |";
    } // else - load text 

    SDL_Texture* text = menu_window.load_from_rendered_text("Select Game to delete, or [A] to DELETE ALL", DEFAULT_WHITE);
    SDL_Texture* game1 = menu_window.load_from_rendered_text(g1, DEFAULT_WHITE);
    SDL_Texture* game2 = menu_window.load_from_rendered_text(g2, DEFAULT_WHITE);
    SDL_Texture* game3 = menu_window.load_from_rendered_text(g3, DEFAULT_WHITE);
    SDL_Texture* game4 = menu_window.load_from_rendered_text(g4, DEFAULT_WHITE);
    SDL_Texture* game5 = menu_window.load_from_rendered_text(g5, DEFAULT_WHITE);


    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 400, 120, 800, 100};
    SDL_Rect g1_target = {GAME_SCREEN_WIDTH / 2 - 400, 300, 800, 50};
    SDL_Rect g2_target = {GAME_SCREEN_WIDTH / 2 - 400, 350, 800, 50};
    SDL_Rect g3_target = {GAME_SCREEN_WIDTH / 2 - 400, 400, 800, 50};
    SDL_Rect g4_target = {GAME_SCREEN_WIDTH / 2 - 400, 450, 800, 50};
    SDL_Rect g5_target = {GAME_SCREEN_WIDTH / 2 - 400, 500, 800, 50};

    SDL_Rect game_background = {GAME_SCREEN_WIDTH / 2 - 450, 280, 900, 300};

    menu_window.render_rect(&game_background, 0x74, 0x6B, 0x5A);
    menu_window.render(text, &text_target);
    menu_window.render(game1, &g1_target);
    menu_window.render(game2, &g2_target);
    menu_window.render(game3, &g3_target);
    menu_window.render(game4, &g4_target);
    menu_window.render(game5, &g5_target);

} // Menu::render_delete_save

void Menu::render_enter_player_name()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("Enter Player Name Below", DEFAULT_WHITE);
    SDL_Texture* return_text = menu_window.load_from_rendered_text("Press [ESCAPE] to go back", DEFAULT_WHITE);
    SDL_Texture* enter_text = menu_window.load_from_rendered_text("Press [ENTER] to Confirm", DEFAULT_WHITE);
    SDL_Texture* name = menu_window.load_from_rendered_text(player_name, DEFAULT_FONT_COLOR);

    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, 200, 400, 100};
    SDL_Rect return_text_target = {GAME_SCREEN_WIDTH / 2 - 150, 600, 300, 60};
    SDL_Rect enter_text_target = {GAME_SCREEN_WIDTH / 2 - 150, 520, 300, 60};
    SDL_Rect input_box = {GAME_SCREEN_WIDTH / 2 - 200, 300, 400, 100};
    SDL_Rect name_target = {GAME_SCREEN_WIDTH / 2 - 200, 300, player_name.length() * 40, 100};
    
    menu_window.render(text, &text_target);
    menu_window.render_rect(&input_box, 0xFF, 0xFF, 0xFF);
    menu_window.render(enter_text, &enter_text_target);
    menu_window.render(name, &name_target);
    menu_window.render(return_text, &return_text_target);
} // Menu::render_enter_player_name

void Menu::render_select_type()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("Select Player Type", DEFAULT_WHITE);
    SDL_Texture* return_text = menu_window.load_from_rendered_text("Press [ESCAPE] to go back", DEFAULT_WHITE);
    SDL_Texture* melee_text = menu_window.load_from_rendered_text("[M] Melee: close range attack with high damage", DEFAULT_WHITE);
    SDL_Texture* projectile_text = menu_window.load_from_rendered_text("[P] Projectile: long range attack with lower damage", DEFAULT_WHITE);
    SDL_Texture* hybrid_text = menu_window.load_from_rendered_text("[H] Hybrid: mixed attacking styles with lower damage", DEFAULT_WHITE);

    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, 100, 400, 100};
    SDL_Rect return_text_target = {GAME_SCREEN_WIDTH / 2 - 150, 600, 300, 60};
    SDL_Rect m_text_target = {GAME_SCREEN_WIDTH / 2 - 400, 250, 800, 50};
    SDL_Rect p_text_target = {GAME_SCREEN_WIDTH / 2 - 400, 350, 800, 50};
    SDL_Rect h_text_target = {GAME_SCREEN_WIDTH / 2 - 400, 450, 800, 50};
    
    menu_window.render(text, &text_target);
    menu_window.render(return_text, &return_text_target);
    menu_window.render(melee_text, &m_text_target);
    menu_window.render(projectile_text, &p_text_target);
    menu_window.render(hybrid_text, &h_text_target);
} // Menu::render_select_type

void Menu::render_admin_pwd()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("Enter Admin Password", DEFAULT_WHITE);
    SDL_Texture* return_text = menu_window.load_from_rendered_text("Press [ESCAPE] to go back", DEFAULT_WHITE);
    SDL_Texture* enter_text = menu_window.load_from_rendered_text("Press [ENTER] to Confirm", DEFAULT_WHITE);
    SDL_Texture* name = menu_window.load_from_rendered_text(pwd, DEFAULT_FONT_COLOR);

    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, 200, 400, 100};
    SDL_Rect return_text_target = {GAME_SCREEN_WIDTH / 2 - 150, 600, 300, 60};
    SDL_Rect enter_text_target = {GAME_SCREEN_WIDTH / 2 - 150, 520, 300, 60};
    SDL_Rect input_box = {GAME_SCREEN_WIDTH / 2 - 200, 300, 400, 100};
    SDL_Rect name_target = {GAME_SCREEN_WIDTH / 2 - 200, 300, pwd.length() * 80, 100};
    
    menu_window.render(text, &text_target);
    menu_window.render_rect(&input_box, 0xFF, 0xFF, 0xFF);
    menu_window.render(enter_text, &enter_text_target);
    menu_window.render(name, &name_target);
    menu_window.render(return_text, &return_text_target);
} // Menu::render_admin_pwd

void Menu::render_complete()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("Gameplay Instructions", DEFAULT_WHITE);
    SDL_Texture* return_text = menu_window.load_from_rendered_text("Press [ESCAPE] to go back", DEFAULT_WHITE);
    SDL_Texture* enter_text = menu_window.load_from_rendered_text("Press [ENTER] to start game", DEFAULT_WHITE);

    SDL_Texture* instructions = menu_window.load_texture("assets/media/menu/instructions.png");

    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, 100, 400, 100};
    SDL_Rect return_text_target = {GAME_SCREEN_WIDTH / 2 - 150, 600, 300, 60};
    SDL_Rect enter_text_target = {GAME_SCREEN_WIDTH / 2 - 150, 520, 300, 60};
    SDL_Rect instructions_target = {GAME_SCREEN_WIDTH / 2 - 400, 220, 800, 300};

    menu_window.render(text, &text_target);
    menu_window.render(return_text, &return_text_target);
    menu_window.render(enter_text, &enter_text_target);
    menu_window.render(instructions, &instructions_target);
}

string Menu::mode_to_text(GameMode mode) const
{
    switch (mode)
    {
        case melee: 
        return "Melee";
        break;

        case projectile:
        return "Projectile";
        break;

        case hybrid:
        return "Hybrid";
        break;

        case admin: 
        return "Admin";
        break;

        default:
        return "";
        break;
    } // switch 
} // Menu::mode_to_text

Menu::~Menu()
{
    // quits text input
    SDL_StopTextInput();
} // destructor
