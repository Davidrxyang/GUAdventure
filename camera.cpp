#include "camera.h"

Camera::Camera()
{
    Camera(0, 0, 0, 0);
} // default constructor

Camera::Camera(int x, int y, int w, int h)
{
    camera.x = x;
    camera.y = y;
    camera.w = w;
    camera.h = h;
} // explicit constructor

