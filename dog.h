#ifndef DOG_H
#define DOG_H

#include <SDL2/SDL.h>
#include "entity.h"
#include <string>

using namespace std;

class Dog : public Entity
{

    public:

        Dog(); // default constructor
        Dog(string name); // explicit constructor - string name
        
        void set_name(string name); // set name
        string get_name() const; // get name
        
    private:

        string name;
        
};

#endif 