#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "entity.h"
#include "window.h"
#include "camera.h"

using namespace std;

class Renderable : public Entity
{
    public:

        Renderable(); // default constructor
        virtual void render(Window window); // render, no animation
        virtual void render(Window window, Camera camera); // camera offset
        virtual void render(Window window, int frame); // render function
        virtual void render(Window window, int frame, Camera camera); // camera offset
        void render_box(Window window);
        void render_box(Window window, Camera camera);
        void modulate_color(Uint8 r, Uint8 g, Uint8 b);
        void modulate_alpha(Uint8 alpha);
        bool has_color_mod() const {return has_c_mod;}; 
        bool has_alpha_mod() const {return has_a_mod;};

    private:

        void position_to_int(); // converts entity position in float to int render pos

        int rx; // converting float position back to ints for the rendering methods
        int ry;

        bool has_c_mod;
        bool has_a_mod;
};

#endif
