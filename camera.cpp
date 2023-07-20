#include "camera.h"

Camera::Camera()
{
    camera -> x = 0;
    camera -> y = 0;
    camera -> w = 0;
    camera -> h = 0;   
} // default constructor

Camera::Camera(int x, int y, int w, int h)
{
    set_x(x);
    set_y(y);
    set_w(w);
    set_h(h);
} // explicit constructor

