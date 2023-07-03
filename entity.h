#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

using namespace std;

class Entity
{

    public: 

        Entity(); // default constructor

        void set_position_x(int x); // set x
        void set_position_y(int y); // set y
        int get_position_x() const; // get x
        int get_position_y() const; // get y

    protected:

        int x; // position x
        int y; // posiiton y
};

#endif