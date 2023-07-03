#include "window.h"

Window::Window()
{
    initialize();

    string window_name = "default window";
    center_x = SDL_WINDOWPOS_CENTERED;
    center_y = SDL_WINDOWPOS_CENTERED;
    width = 680;
    height = 480;

    window = build_window(window_name, center_x, center_y, width, height);   

    if(!window)
    {
        cout << "Failed to create window: " << SDL_GetError();
    } // if

    window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        cout << "Failed to get the surface from the window: " << SDL_GetError();
    } // if

    SDL_UpdateWindowSurface(window);
} // Window::Window default constructor             

Window::Window(string name)
{
    initialize();
    
    center_x = SDL_WINDOWPOS_CENTERED;
    center_y = SDL_WINDOWPOS_CENTERED;
    width = 680;
    height = 480;

    window = build_window(name, center_x, center_y, width, height);
    if(!window)
    {
        cout << "Failed to create window: " << SDL_GetError();
    } // if

    window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        cout << "Failed to get the surface from the window: " << SDL_GetError();
    } // if
} // Window::Window explicit constructor with name

Window::Window(string name, int x, int y, int w, int h)
{
    initialize();
    window = build_window(name, x, y, w, h);
    if(!window)
    {
        cout << "Failed to create window: " << SDL_GetError();
    } // if

    window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        cout << "Failed to get the surface from the window: " << SDL_GetError();
    } // if
} // Window::Window - explicit constructor with dimensions

SDL_Window* Window::build_window(string window_name, int center_x, int center_y, int width, int height)
{
    const char* title = window_name.c_str();
    return SDL_CreateWindow(title, center_x, center_y, width, height, 0);
} // Window::build_window - private build window member function, builds SDL window with specified dimensions

void Window::initialize() const
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "ERROR - Failed to initialize SDL2 library: \n";
        cout << SDL_GetError();
    } // if
} // Window::initialize - initializes the SDL2 library

void Window::test_run() const
{
    bool isquit = false;
    SDL_Event test_event;
    while (!isquit) {
        if (SDL_PollEvent( & test_event)) {
            if (test_event.type == SDL_QUIT) {
                isquit = true;
            } // if
        } // if
    } // while
} // Window::test_run - runs a test event