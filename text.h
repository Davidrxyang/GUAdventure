#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <string>
#include "window.h"
#include "renderable.h"


using namespace std;

class Text : public Renderable
{

    public:

        Text(); // default constructor
        Text(string input_text, Window window, SDL_Color font_color); // explicit constructor
        
        void set_text(string input_text) {this -> input_text = input_text;}; // set name
        string get_text() const {return input_text;}; // get name
        void handle_text_event(SDL_Event& e); // handle input event - text input
        void clear() {input_text = " ";}; // clear
        void render_text(Window window); // render

    private:

        string input_text;
        bool has_text;
        SDL_Color font_color;
};

#endif 