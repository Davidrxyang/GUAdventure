#include "renderable.h"

Renderable::Renderable() : Entity()
{

} // default constructor - empty 

void Renderable::render(Window window) const
{
    SDL_Rect target = {x, y, w, h};
    target.x = x;
    target.y = y; // update position components as necessary
    window.render(sprite_sheet, &target, nullptr, angle, nullptr, flip);
} // Renderable::render - no frame animation

void Renderable::render(Window window, int cam_x, int cam_y) const
{
    SDL_Rect target = {x, y, w, h};
    target.x = x - cam_x;
    target.y = y - cam_y; // update position components as necessary
    window.render(sprite_sheet, &target, nullptr, angle, nullptr, flip);
} // Renderable::render - no frame animation - offset for camera

void Renderable::render(Window window, int frame) const
{
    SDL_Rect target = {x, y, w, h};
    target.x = x;
    target.y = y; // update position components as necessary
    SDL_Rect current_frame = get_frame(frame / 4); // TODO set global constant animation rate speed
    window.render(sprite_sheet, &target, &current_frame, angle, nullptr, flip);
} // Renderable::render - frame animation

void Renderable::render(Window window, int frame, int cam_x, int cam_y) const
{
    SDL_Rect target = {x, y, w, h};
    target.x = x - cam_x;
    target.y = y - cam_y; // update position components as necessary
    SDL_Rect current_frame = get_frame(frame / 4); // TODO set global constant animation rate speed
    window.render(sprite_sheet, &target, &current_frame, angle, nullptr, flip);
} // Renderable::render - frame animation - offset for camera

void Renderable::render_box(Window window) const
{
    SDL_SetRenderDrawColor(window.get_renderer(), 0, 0xFF, 0, SDL_ALPHA_OPAQUE);
    // sets collision box color to cyan 
    SDL_RenderDrawRect(window.get_renderer(), &collision_box);
} // Entity::render_box - for entity interaction testing purposes