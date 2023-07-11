#ifndef DOG_H
#define DOG_H

#include <SDL2/SDL.h>
#include <string>
#include "entity.h"
#include "window.h"

using namespace std;

class Dog : public Entity
{

    public:

        Dog(); // default constructor
        Dog(string name, Window window); // explicit constructor, spec name and window
        
        void set_name(string name); // set name
        string get_name() const; // get name

    private:

        string name;
};

#endif 