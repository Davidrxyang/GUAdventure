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

    private:

        void position_to_int(); // converts entity position in float to int render pos

        int rx; // converting float position back to ints for the rendering methods
        int ry;
};

#endif
