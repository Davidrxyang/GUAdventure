#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player
{
    public:
        Player();
        Player(string name);
        void set_player_name(string name);
        string get_player_name() const;
        void set_score(int s) {score = s;}; // set score
        void increment_score() {score++;}; // increment score
        int get_score() const {return score;}; // get score
    
    private:
        string player_name;
        int score;
};

#endif