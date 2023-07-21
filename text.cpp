#include "text.h"

Text::Text() : Renderable()
{
    SDL_StartTextInput();
    font_color = DEFAULT_FONT_COLOR;
    input_text = "";
    sprite_sheet = nullptr;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    collision_box.x = x;
    collision_box.y = y;
    collision_box.w = w;
    collision_box.h = h;
    has_text = true;
} // default constructor

Text::Text(string input_text, Window window, SDL_Color font_color) : Renderable()
{
    SDL_StartTextInput();
    this -> font_color = font_color;
    this -> input_text = input_text;
    sprite_sheet = window.load_from_rendered_text(input_text, font_color);
    x = 0;
    y = 0;
    w = input_text.size() * 20;
    h = 200;
    collision_box.x = x;
    collision_box.y = y;
    collision_box.w = w;
    collision_box.h = h;
    has_text = true;
} // explicit constructor

void Text::handle_text_event(SDL_Event& e)
{
    handle_event(e);
    
    if (e.type == SDL_KEYDOWN)
    {
        // text input testing
        if (e.key.keysym.sym  == SDLK_BACKSPACE
        && input_text.size() > 0)
        {
            input_text.pop_back();
            has_text = true;
        } // if - backspace to lop off character
    } // if - the event type is keydown - BACKSPACE
    else if (e.type == SDL_TEXTINPUT)
    {
        input_text += e.text.text;
        has_text = true;
    } // else if - if not backspace, the text input is handled as a different
    w = input_text.size() * 20;
    update_box();
} // Text::handle_text_event

void Text::render_text(Window window)
{
    if (sprite_sheet == nullptr)
    {
        sprite_sheet = window.load_from_rendered_text(input_text, DEFAULT_FONT_COLOR);
    } // if - no text 
    if (has_text)
    {
        if (input_text != "")
        {
            sprite_sheet = window.load_from_rendered_text(input_text, font_color);
            render(window);
        } // if - text is not empty
        else
        {
            sprite_sheet = window.load_from_rendered_text(" ", font_color);
            render(window);
        } // else - text is empty
    } // if - has text
} // Text::render_text