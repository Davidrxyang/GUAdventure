#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "camera.h"

#include "CONSTANTS.h"

using namespace std;

class Window
{

    public:

        Window(); // constructor
        Window(string name); // create a default window
        Window(string name, int x, int y, int w, int h); // window with dimensions
        Window(string name, int x, int y, int w, int h, string font_path, int font_size); // window with dimensions and font
        
        void set_name(string name); // set name
        void set_font(string font_path, int font_size, Uint8 r, Uint8 g, Uint8 b); // set font
        bool set_background(string media_path); // loads background texture
        void set_background_width(int w) {background_width = w;}; // set background width
        void set_background_height(int h) {background_height = h;}; // set background height
        int get_background_width() const {return background_width;}; // getter
        int get_background_height() const {return background_height;}; // getter
        void set_local_text(string text); // sets the local text
        SDL_Texture* get_background() const {return background;}; // get background
        SDL_Texture* get_text() const {return text_texture;}; // get text
        int get_width() const {return width;}; // get width
        int get_height() const {return height;}; // get height
        SDL_Renderer* get_renderer() const {return renderer;}; // get renderer
        
        bool load_media(); // load preset media files
        bool load_media(string media_path); // load a specfic media file
        SDL_Surface* load_surface(string media_path); // TODO implement format optimization
        SDL_Texture* load_texture(string media_path); // load a fast SDL texture
        SDL_Texture* load_texture(string media_path, Uint8 key_r, Uint8 key_g, Uint8 key_b); // load texture with colorkey
        SDL_Texture* load_from_rendered_text(string text, SDL_Color text_color); // load TTF text as texture
        SDL_Texture* texture_from_surface(SDL_Surface* surface); // wrap SDL function to convert surface to texture
        SDL_Texture* texture_from_surface(SDL_Surface* surface, Uint8 key_r, Uint8 key_g, Uint8 key_b); // with color key

        // wrapping render and update functions from SDL in class methods
        void render(SDL_Texture* texture) const; // renders to full screen
        void render(SDL_Texture* texture, SDL_Rect* target) const; // renders to a position and size on the screen
        void render(SDL_Texture* texture, SDL_Rect* target, SDL_Rect* clip) const; // clip rendering
        void render(SDL_Texture* texture, SDL_Rect* target, SDL_Rect* clip, double rotate_angle, 
                    SDL_Point* rotate_center, SDL_RendererFlip flip) const; // render with rotation specs
        void render_background(Camera camera);
        void render_rect(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b); // render a rectangle

        // render conditions
        void render_clear() const; // clears renderer
        void update_screen() const; // updates screen, renders to screen

        // modulate texture 
        void modulate_color(SDL_Texture* texture, Uint8 r, Uint8 g, Uint8 b) const; // modulate texture color
        void modulate_alpha(SDL_Texture* texture, Uint8 alpha) const; // alpha blending, modulate transparency

        void close_window(); // TODO implement quit function
                
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
        TTF_Font* font;
        SDL_Color font_color;

        SDL_Texture* texture;
        SDL_Texture* text_texture;
        SDL_Surface* temp_image;
        SDL_Surface* window_surface;
        SDL_Surface* KeyPress[key_total]; // TESTING array for corresponding keypress surfaces
        SDL_Rect rect; // TESTING

        // background
        SDL_Texture* background;
        int background_width;
        int background_height;

        SDL_Window* window;
        SDL_Renderer* renderer;
};

#endif