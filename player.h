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
    
    private:
        string player_name;
};

#endif