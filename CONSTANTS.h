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
const double DAWG_RAND_SPEED_MID = 200;
const int DAWG_RAND_SPEED_RANGE = 400; // + - this to MID for randomized speed range, int for % operator

// change rate for randomization based on frame count
const int RATE_RAND_MID = 100; // every one hundred frames, activate randomized speed change
const int RATE_RANT_RANGE = 30; // this is the variance for above variable

// interaction distances
const double REBOUND_DISTANCE = 30; // rebound distance

// health
const int MAX_HEALTH = 10;
const int HEALTH_BAR_UNIT_LENGTH = 8;
const int HEALTH_BAR_HEIGHT = 10;

// animation
const int ANIMATION_FRAME_COUNT = 4;

// text
const string DEATH_MESSAGE = "YOU DIED ... ";
const string VICTORY_MESSAGE = "YOU WIN ... ";
const int CENTER_MESSAGE_W = 800;
const int CENTER_MESSAGE_H = 300;
const int CENTER_MESSAGE_X = GAME_SCREEN_WIDTH / 2 - CENTER_MESSAGE_W / 2; 
const int CENTER_MESSAGE_Y = GAME_SCREEN_HEIGHT / 2 - CENTER_MESSAGE_H / 2;
const SDL_Rect CENTER_TEXT_TARGET = {CENTER_MESSAGE_X, CENTER_MESSAGE_Y, CENTER_MESSAGE_W, CENTER_MESSAGE_H};

// game play variables
const int HEAL_AMOUNT = 2;
const int ENEMY_DAMAGE = 1;
const int DEFAULT_ENEMY_COUNT = 20;

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

enum HealthState
{
    health_state_normal,
    health_state_max,
    health_state_min,
};

#endif