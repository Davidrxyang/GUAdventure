#ifndef DOG_H
#define DOG_H

#include <SDL2/SDL.h>
#include <string>
#include "window.h"
#include "renderable.h"
#include "particle.h"
#include "camera.h"

using namespace std;

class Dog : public Renderable
{

    public:

        Dog(); // default constructor
        Dog(string name, Window window); // explicit constructor, spec name and window
        // ~Dog(); // destructor TODO MOVE THIS TO MAIN GAME DESTRUCTOR WHEN BUILT
        
        void set_name(string name) {this -> name = name;}; // set name
        string get_name() const {return name;}; // get name
        void render_dog(Window window, int frame, Camera camera); // render 

    private:

        string name;

        // particle engine
        Particle* particles[TOTAL_PARTICLES];
        void render_particles(Window window, Camera camera);

};

#endif 