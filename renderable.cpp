#include "renderable.h"

Renderable::Renderable() : Entity()
{
    rx = int(x);
    ry = int(y);
    has_c_mod = false;
    has_a_mod = false;
} // default constructor - empty 

void Renderable::position_to_int() 
{
    rx = int(x);
    ry = int(y);
} // Renderable::position_to_int

void Renderable::render(Window window)
{
    position_to_int();
    SDL_Rect target = {rx, ry, w, h};
    target.x = rx;
    target.y = ry; // update position components as necessary
    window.render(sprite_sheet, &target, nullptr, angle, nullptr, flip);
} // Renderable::render - no frame animation

void Renderable::render(Window window, Camera camera)
{
    position_to_int();
    SDL_Rect target = {rx, ry, w, h};
    target.x = rx - camera.get_x();
    target.y = ry - camera.get_y(); // update position components as necessary
    window.render(sprite_sheet, &target, nullptr, angle, nullptr, flip);
} // Renderable::render - no frame animation - offset for camera

void Renderable::render(Window window, int frame)
{
    position_to_int();
    SDL_Rect target = {rx, ry, w, h};
    target.x = rx;
    target.y = ry; // update position components as necessary
    SDL_Rect current_frame = get_frame(frame / 4); // TODO set global constant animation rate speed
    window.render(sprite_sheet, &target, &current_frame, angle, nullptr, flip);
} // Renderable::render - frame animation

void Renderable::render(Window window, int frame, Camera camera)
{
    position_to_int();
    SDL_Rect target = {rx, ry, w, h};
    target.x = rx - camera.get_x();
    target.y = ry - camera.get_y(); // update position components as necessary
    SDL_Rect current_frame = get_frame(frame / 4); // TODO set global constant animation rate speed
    window.render(sprite_sheet, &target, &current_frame, angle, nullptr, flip);
} // Renderable::render - frame animation - offset for camera

void Renderable::render_box(Window window) 
{
    position_to_int();
    SDL_SetRenderDrawColor(window.get_renderer(), 0, 0xFF, 0, SDL_ALPHA_OPAQUE);
    // sets collision box color to cyan 
    SDL_RenderDrawRect(window.get_renderer(), &collision_box);
} // Renderable::render_box - for entity interaction testing purposes

void Renderable::render_box(Window window, Camera camera) 
{
    position_to_int();
    SDL_SetRenderDrawColor(window.get_renderer(), 0, 0xFF, 0, SDL_ALPHA_OPAQUE);
    // sets collision box color to cyan 
    SDL_Rect temp_box = collision_box;
    temp_box.x -= camera.get_x();
    temp_box.y -= camera.get_y();
    SDL_RenderDrawRect(window.get_renderer(), &temp_box);
} // Renderable::render_box - for entity interaction testing purposes

void Renderable::modulate_color(Uint8 r, Uint8 g, Uint8 b) 
{
    SDL_SetTextureColorMod(sprite_sheet, r, g, b);
    
    if (r == 0xFF && g == 0xFF && b == 0xFF)
    {
        has_c_mod = false;
    } // if - set color state
    else
    {
        has_c_mod = true;
    } // else
} // Renderable::modulate_color

void Renderable::modulate_alpha(Uint8 alpha) 
{
    SDL_SetTextureBlendMode(sprite_sheet, SDL_BLENDMODE_BLEND); // enables blending
    SDL_SetTextureAlphaMod(sprite_sheet, alpha); // alpha blending - TRANSPARENCY OF TEXTURE
    
    if (alpha == 0xFF)
    {
        has_a_mod = false;
    } // if - set color state
    else
    {
        has_a_mod = true;
    }
} // Renderable::modulate_alpha
