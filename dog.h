#ifndef DOG_H
#define DOG_H

#include <SDL2/SDL.h>
#include <string>
#include "window.h"
#include "renderable.h"
#include "perishable.h"
#include "particle.h"
#include "projectile.h"
#include "melee.h"
#include "camera.h"
#include "timer.h"

using namespace std;

const size_t TOTAL_PROJECTILES = 10; 

class Dog : public Perishable
{

    public:

        Dog(); // default constructor
        Dog(string name, double x, double y, Window window); // explicit constructor, spec name and window
        // ~Dog(); // destructor TODO MOVE THIS TO MAIN GAME DESTRUCTOR WHEN BUILT
        
        void set_name(string name) {this -> name = name;}; // set name
        string get_name() const {return name;}; // get name
        void render(Window window, int frame, Camera camera); // render - polymorphism
        void handle_event(SDL_Event& e); // handle event - polymorphism
        void move(Window window, double time_step); // move
        void fire_projectile(); // fire projectile with current entity direction
        void fire_projectile(Direction direction); // fire projectile with spec direction
        void kill_projectiles();
        vector<Projectile*> get_projectiles() {return projectiles;}; // get projectiles

        void melee_attack(); // melee attack
        void reset_melee(); // reset melee
        Melee get_melee() {return melee;}; // get melee

    private:

        string name;

        // particle engine
        vector<Particle*> particles;
        void render_particles(Window window, Camera camera);
        
        // projectiles
        vector<Projectile*> projectiles;
        void fire_projectile(int current_projectile, Direction direction);
        void render_projectiles(Window window, Camera camera);
        size_t projectile_counter;

        // melee
        Melee melee;
};


#endif 