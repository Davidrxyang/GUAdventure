#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SDL2/SDL.h"
#include "window.h"

using namespace std;

// ALL DATA FOR GAME AND GAME ENGINE STORED HERE FOR EASY MANIPULATION

// game dimensions
const int GAME_SCREEN_WIDTH = 1200;
const int GAME_SCREEN_HEIGHT = 500;
const int GAME_LEVEL_WIDTH = 3000;
const int GAME_LEVEL_HEIGHT = 1500;
const int DATA_PANEL_WIDTH = GAME_SCREEN_WIDTH;
const int DATA_PANEL_HEIGHT = 80;

// default colors
const SDL_Color DEFAULT_BLACK = {0, 0, 0};
const SDL_Color DEFAULT_WHITE = {0xFF, 0xFF, 0xFF};
const SDL_Color DEFAULT_FONT_COLOR = {0, 0, 0};

// data panel
const int DATA_PANEL_X = 0;
const int DATA_PANEL_Y = GAME_SCREEN_HEIGHT;
const SDL_Rect DATA_PANEL = {DATA_PANEL_X, DATA_PANEL_Y, DATA_PANEL_WIDTH, DATA_PANEL_HEIGHT};

// particles and projectiles
const size_t TOTAL_PROJECTILES = 10; 
const int TOTAL_PARTICLES = 10;

// speeds
const double PROJECTILE_SPEED = 2500;
const double DEFAULT_SPEED = 1000; // pixels per SECOND
const double DAWG_RAND_SPEED_MID = 200;

// change rate for randomization based on frame count
const int RATE_RAND_MID = 100; // every one hundred frames, activate randomized speed change
const int RATE_RANT_RANGE = 30; // this is the variance for above variable

// interaction distances
const double REBOUND_DISTANCE = 50; // rebound distance

// health
const int MAX_HEALTH = 10;
const int HEALTH_BAR_UNIT_LENGTH = 8;
const int HEALTH_BAR_HEIGHT = 10;

// animation
const int ANIMATION_FRAME_COUNT = 4;

// text
const string DEATH_MESSAGE = "YOU DIED ... ";
const string VICTORY_MESSAGE = "YOU WIN ... ";
const int CENTER_MESSAGE_W = 1000;
const int CENTER_MESSAGE_H = 300;
const int CENTER_MESSAGE_X = GAME_SCREEN_WIDTH / 2 - CENTER_MESSAGE_W / 2; 
const int CENTER_MESSAGE_Y = GAME_SCREEN_HEIGHT / 2 - CENTER_MESSAGE_H / 2;
const SDL_Rect CENTER_TEXT_TARGET = {CENTER_MESSAGE_X, CENTER_MESSAGE_Y, CENTER_MESSAGE_W, CENTER_MESSAGE_H};

// game play variables
const int HEAL_AMOUNT = 2;
const int ENEMY_DAMAGE = 1;
const size_t DEFAULT_ENEMY_COUNT = 20;
const size_t INITIAL_ENEMY_COUNT = 5;
const int ENEMY_COUNT_INCREMENT_FACTOR = 2;

// menu
const int MAX_PLAYER_NAME_LENGTH = 10;

// directions 
enum Direction
{
    DEFAULT,
    UP,
    DOWN,
    LEFT,
    RIGHT,
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

// entity health states
enum HealthState
{
    health_state_normal,
    health_state_max,
    health_state_min,
};

// game exit states
enum GameEndState
{
    game_default,
    game_victory,
    game_defeat,
    game_quit,
};

// menu function states
enum MenuFunction
{
    menu_default,
    menu_enter_player_name,
}; // TODO ADD MORE LATER

// menu exit states
enum MenuExitState
{
    menu_exit_default,
    menu_exit_success,
    menu_exit_failed,
    menu_quit,
};

// game modes
enum GameMode
{
    normal,
    admin,
};

#endif