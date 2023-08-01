#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SDL2/SDL.h"
#include "window.h"

using namespace std;

// ALL DATA FOR GAME AND GAME ENGINE STORED HERE FOR EASY MANIPULATION

// game dimensions
const int GAME_SCREEN_WIDTH = 1400;
const int GAME_SCREEN_HEIGHT = 600;
const int GAME_LEVEL_WIDTH = 3000;
const int GAME_LEVEL_HEIGHT = 1500;

// default colors
const SDL_Color DEFAULT_BLACK = {0, 0, 0};
const SDL_Color DEFAULT_FONT_COLOR = {0, 0, 0};

// particles and projectiles
const size_t TOTAL_PROJECTILES = 10; 
const int TOTAL_PARTICLES = 10;

// speeds
const double PROJECTILE_SPEED = 2500;
const double DEFAULT_SPEED = 1000; // pixels per SECOND

// interaction distances
const double REBOUND_DISTANCE = 30; // rebound distance

// health
const int MAX_HEALTH = 10;
const int HEALTH_BAR_UNIT_LENGTH = 8;
const int HEALTH_BAR_HEIGHT = 10;

// animation
const int animation_frame_count = 4;

// directions 
enum Direction
{
    DEFAULT,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

// key presses
enum KeyPress
{
    key_default,
    key_up,
    key_down,
    key_left,
    key_right,
    key_total,
};

// mouse states
enum MouseState
{
    button_mouse_out,
    button_mouse_over,
    button_mouse_down,
    button_mouse_up,
    button_mouse_total,
};

#endif