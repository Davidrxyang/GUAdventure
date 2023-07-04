#ifndef LEVEL_H
#define LEVEL_H

#include<SDL2/SDL.h>
#include<string>

using namespace std;

class Level
{

    public:
        Level(); // default constructor
        Level(string name); // explicit constructor
        void set_name(string name); // set name
        string get_name() const;

    private:
        string name;

};

#endif