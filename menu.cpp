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

                case menu_complete:
                is_quit = true;

                if (player -> get_player_name() == "AdminDavid"
                || player -> get_player_name() == "AdminAdmin"
                
                // ADD ADDITIONAL ADMIN USERNAMES HERE
                
                )
                {
                    player -> set_mode(admin);
                } // set admin mode 
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
            function = menu_select_type;
            break;

            // handle backspace
            case SDLK_BACKSPACE:
            if (player_name.length() > 0)
            {
                player_name.pop_back();
            } // if - backspace
    
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
            case SDLK_1:
            player -> set_mode(melee);
            new_game();
            function = menu_complete;
            break;

            case SDLK_2:
            player -> set_mode(projectile);
            new_game();
            function = menu_complete;
            break;

            case SDLK_3:
            player -> set_mode(hybrid);
            new_game();
            function = menu_complete;
            break;

            default:
            break;
        } // switch - mode
    } // if - keydown
} // Menu::select_player_type

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
    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, 20, 400, 200};
    menu_window.render(text, &text_target);
} // Menu::render_title

void Menu::render_select_game()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("Select Game", DEFAULT_WHITE);
    SDL_Rect text_target = {0, 0, 200, 200};

    menu_window.render(text, &text_target);
} // Menu::render_select_game

void Menu::render_enter_player_name()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("Enter Player Name Below", DEFAULT_WHITE);
    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, GAME_SCREEN_HEIGHT / 3 + 80, 400, 100};
    SDL_Rect input_box = {GAME_SCREEN_WIDTH / 2 - 200, GAME_SCREEN_HEIGHT / 3 + 200, 400, 100};
    SDL_Texture* name = menu_window.load_from_rendered_text(player_name, DEFAULT_FONT_COLOR);
    SDL_Rect name_target = {GAME_SCREEN_WIDTH / 2 - 200, GAME_SCREEN_HEIGHT / 3 + 200, player_name.length() * 40, 100};
    
    menu_window.render(text, &text_target);
    menu_window.render_rect(&input_box, 0xFF, 0xFF, 0xFF);
    menu_window.render(name, &name_target);
} // Menu::render_enter_player_name

void Menu::render_select_type()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("Select Type", DEFAULT_WHITE);
    SDL_Rect text_target = {0, 0, 200, 200};

    menu_window.render(text, &text_target);
} // Menu::render_select_type

Menu::~Menu()
{
    // quits text input
    SDL_StopTextInput();
} // destructor
