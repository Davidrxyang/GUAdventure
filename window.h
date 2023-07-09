#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

using namespace std;

enum KeyPress
{
    key_default,
    key_up,
    key_down,
    key_left,
    key_right,
    key_total,
};

class Window
{

    public:

        Window(); // constructor
        Window(string name); // create a default window
        Window(string name, int x, int y, int w, int h); // window with specified dimensions
        
        void set_name(string name);

        bool set_background(string media_path); // loads background texture
        bool load_media(); // load preset media files
        bool load_media(string media_path); // load a specfic media file
        
        SDL_Surface* load_surface(string media_path); // TODO implement format optimization
        
        SDL_Texture* load_texture(string media_path); // load a fast SDL texture
        SDL_Texture* load_texture(string media_path, Uint8 key_r, Uint8 key_g, Uint8 key_b); // load texture with colorkey
        SDL_Texture* texture_from_surface(SDL_Surface* surface); // wrap SDL function to convert surface to texture
        SDL_Texture* texture_from_surface(SDL_Surface* surface, Uint8 key_r, Uint8 key_g, Uint8 key_b); // with color key

        // wrapping render and update functions from SDL in class methods
        void render(SDL_Texture* texture) const; // renders to full screen
        void render(SDL_Texture* texture, SDL_Rect* rect) const; // renders to a position and size on the screen
        void render(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* clip) const; // clip rendering
        void render_clear() const; // clears renderer
        void update_screen() const; // updates screen, renders to screen
        void modulate_color(SDL_Texture* texture, Uint8 r, Uint8 g, Uint8 b) const; // modulate texture color
        void modulate_alpha(SDL_Texture* texture, Uint8 alpha) const; // alpha blending, modulate transparency

        void close_window(); // close the window
        
        bool test_run_1();
        bool test_run_2();

    private:
        
        // private functions

        SDL_Window* build_window(int, int, int, int); // builds window
        SDL_Renderer* build_renderer(SDL_Window* temp_window); // builds renderer for specified window
        bool initialize() const;

        // window data dimensions

        int center_x;
        int center_y;
        int width;
        int height;
        string window_name;

        SDL_Texture* background;
        SDL_Texture* texture;
        SDL_Surface* temp_image;
        SDL_Surface* window_surface;
        SDL_Surface* KeyPress[key_total]; // TESTING array for corresponding keypress surfaces
        SDL_Rect rect; // TESTING

        SDL_Window* window;
        SDL_Renderer* renderer;
};

#endif