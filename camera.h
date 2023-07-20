#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Camera
{
    public:

        Camera(); // default constructor
        Camera(int x, int y, int w, int h); // explicit constructor
        void set_x(int x) { camera.x = x;}; 
        void set_y(int y) { camera.y = y;};
        void set_w(int w) { camera.w = w;}; 
        void set_h(int h) { camera.h = h;}; 
        int get_x() const {return camera.x;};
        int get_y() const {return camera.y;};
        int get_w() const {return camera.w;};
        int get_h() const {return camera.h;};

    private:
        
        SDL_Rect camera;
};

#endif