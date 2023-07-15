#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "entity.h"
#include "window.h"

using namespace std;

class Renderable : public Entity
{
    public:

        Renderable(); // default constructor
        void render(Window window) const; // render, no animation
        void render(Window window, int frame) const; // render function
        void render_box(Window window) const;
};

#endif
