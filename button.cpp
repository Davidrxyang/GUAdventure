#include "button.h"

Button::Button()
{
   position.x = 0;
   position.y = 0;
   button_width = 100;
   button_height = 100;
   texture = nullptr;
   current_state = button_mouse_out;
} // default constructor

Button::Button(int x, int y, int w, int h, Window window, string media_path)
{
    position.x = x;
    position.y = y;
    button_width = w;
    button_height = h;
    current_state = button_mouse_out;
    texture = window.load_texture(media_path.c_str());
} // Button::Button

void Button::set_position(int x, int y)
{
    position.x = x;
    position.y = y;
} // Button::set_posiiton

void Button::set_texture(Window window, string media_path)
{
    texture = window.load_texture(media_path.c_str());
} // Button::set_texture

void Button::handle_event(SDL_Event* event)
{
    // this function is iterated within the game while loop
    // check if event is a mouse event
    if (event -> type == SDL_MOUSEMOTION || 
        event -> type == SDL_MOUSEBUTTONDOWN ||
        event -> type == SDL_MOUSEBUTTONUP)
    {
        // BUTTONMOTION - mouse moves
        // BUTTONDOWN - mouse click down
        // BUTTONUP - mouse click up, mouse release
         int x, y;
         SDL_GetMouseState(&x, &y);

        // check if the mouse is inside the button 

         bool inside = true;
        if (x < position.x)
        {
            inside = false;
        } // if
        else if (x > position.x + button_width)
        {
            inside = false;
        } // else if
        else if (y < position.y) 
        {
            inside = false;
        } // else if
        else if (y > position.y + button_height)
        {
        inside = false;
        } // else if

        if (!inside) // mouse is not inside the button
        {
            current_state = button_mouse_out;
        } // if

        else // mouse is inside the button
        {
            switch (event -> type)
            {
                case SDL_MOUSEMOTION:
                current_state = button_mouse_over;
                break;

                case SDL_MOUSEBUTTONDOWN:
                current_state = button_mouse_down;
                break;

                case SDL_MOUSEBUTTONUP:
                current_state = button_mouse_up;
                break;
            } // switch
        } // else - mouse is inside button
    } // if - event is of mouse type 
} // Button::handle_event

void Button::render(Window window)
{
    SDL_Rect rect = {position.x, position.y, button_width, button_height};
    SDL_Rect clips[button_mouse_total];

    for (size_t i = 0; i < button_mouse_total; i++)
    {
        clips[i].x = 0;
        clips[i].y = i * 200;
        clips[i].w = button_width;
        clips[i].h = button_height;
    }
    window.render(texture, &rect, &clips[current_state]);
} // Button::render