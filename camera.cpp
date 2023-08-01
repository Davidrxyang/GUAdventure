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

void Camera::process_camera(SDL_Rect box, int screen_width, int screen_height, int level_width, int level_height)
{
    // PROCESS CAMERA
    camera.x = ((box.x + box.w / 2) - screen_width / 2);
    camera.y = ((box.y + box.h / 2) - screen_height / 2);

    // camera bounds checking
    if (camera.x < 0)
    {
        camera.x = 0;
    } // if
    if (camera.y < 0)
    {
        camera.y = 0;
    } // if
    if (camera.x > level_width - camera.w)
    {
        camera.x = level_width - camera.w;
    } // if
    if (camera.y > level_height - camera.h)
    {
        camera.y = level_height - camera.h;
    } // if
} // Game::process_camera
