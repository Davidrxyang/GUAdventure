#include "menu.h"

Menu::Menu()
{
    is_quit = true;
    player_name = "";
    // calls default constructors
} // Default Constructor

Menu::Menu(Player* player, Window window)
{
    is_quit = true;
    menu_window = window;
    player_name = "";
    this -> player = player;
} // explicit constructor

MenuExitState Menu::start_menu()
{
    is_quit = false;
    int frame = 0;
    SDL_Event menu_event;
    menu_window.set_background("assets/media/background/menu.png");
    function = menu_enter_player_name;
    
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
            case menu_enter_player_name:
            render_enter_player_name();
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
            else if (menu_event.type == SDL_KEYDOWN)
            {
                switch (menu_event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                    if (player_name == "")
                    {
                        player_name = " ";
                    } // if - empty, add space for rendering purposes
                    player -> set_player_name(player_name);
                    is_quit = true;
                    return menu_exit_success;
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

            switch(function)
            {
                case menu_enter_player_name:
                enter_player_name(menu_event);
                break;

                default:
                break;
            } // switch - current menu function
        } // if - poll event
    } // while - runs while not quit

    // exit success
    return menu_exit_success;
} // Menu::start_menu

int Menu::poll_event(SDL_Event* e)
{
    return SDL_PollEvent(e);
} // Game::poll_event

void Menu::initialize()
{
    // initialize text input
    SDL_StartTextInput();
} // Menu::initialize

void Menu::render_title()
{
    SDL_Texture* text = menu_window.load_from_rendered_text("MENU", DEFAULT_WHITE);
    SDL_Rect text_target = {GAME_SCREEN_WIDTH / 2 - 200, 20, 400, 200};
    menu_window.render(text, &text_target);
} // Menu::render_title

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

void Menu::enter_player_name(SDL_Event &e)
{
    if (e.type == SDL_TEXTINPUT)
    {
        if (!empty_name && player_name.length() < MAX_PLAYER_NAME_LENGTH)
        {
            player_name += e.text.text;
        } // if - name length bounds checking
    } // if - text input
} // Menu::enter_player_name

Menu::~Menu()
{
    // quits text input
    SDL_StopTextInput();
} // destructor

