#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "CONSTANTS.h"

using namespace std;

class Player
{
    public:
        Player();
        Player(string name);
        void set_player_name(string name);
        void set_score(int s) {score = s;}; // set score
        void increment_score() {score++;}; // increment score
        void set_mode(GameMode mode) {this -> mode = mode;}; // set game mode
        void set_health(size_t health) {this -> health = health;}; // set health
        void set_level(size_t level) {this -> level = level;}; // set level
        void set_remaining_enemies(size_t enemies) {remaining_enemies = enemies;}; // set enemies
        void set_x(double x) {this -> x = x;}; // set x
        void set_y(double y) {this -> y = y;}; // set y
        
        string get_player_name() const;
        size_t get_score() const {return score;}; // get score
        GameMode get_mode() const {return mode;}; // get mode
        size_t get_health() const {return health;}; // get health
        size_t get_level() const {return level;}; // get level
        size_t get_remaining_enemies() const {return remaining_enemies;}; // get r enemies
        double get_x() const {return x;}; // get x
        double get_y() const {return y;}; // get y

    private:
        string player_name;
        size_t score;
        GameMode mode;

        // for save game
        size_t health;
        size_t level;
        size_t remaining_enemies;
        double x;
        double y;
};

#endif