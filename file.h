#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include "CONSTANTS.h"

using namespace std;

class GameFile
{
    public:

        GameFile(); // default constructor
        void read(string file_path); // reads a file
        void write(string file_path, string p_name, 
        int p_type, size_t c_level, size_t c_score, size_t r_enemies, size_t health);
        void write(string file_path);
        
        // accessors
        bool empty(string file_path); // is empty
        string get_name() const {return player_name;};
        GameMode get_player_mode() const {return player_mode;};
        size_t get_current_level() const {return current_level;};
        size_t get_current_score() const {return current_score;};
        size_t get_remaining_enemies() const {return remaining_enemies;};
        size_t get_health() const {return health;};

    private:

        // game data members
        string player_name;
        int player_type;
        GameMode player_mode;
        size_t current_level;
        size_t current_score;
        size_t remaining_enemies;
        size_t health;
        bool is_empty;

        string read_string(istream& in_file) const; // read double quoted string
};

#endif