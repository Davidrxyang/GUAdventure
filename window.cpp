#include "window.h"

Window::Window()
{
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

bool Window::initialize() const // private member function
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Failed to initialize SDL2 library: " << SDL_GetError() << endl;
        success = false;
    } // if

    return success;
} // Window::initialize - initializes the SDL2 library

bool Window::load_media(string media_path)
{
    bool success = true;
    image = nullptr;

    image = SDL_LoadBMP(media_path.c_str());

    if (image == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        cout << "Image path: " << media_path << endl;
        success = false;
    }

    return success;
} // Window::load_media

void Window::close_window()
{

    // frees allocated image surface
    SDL_FreeSurface(image);
    image = nullptr;

    // this frees window and the window surface
    SDL_DestroyWindow(window);
    window = nullptr;

    // quit sdl
    SDL_Quit();
} // Window::close_window






bool Window::test_run()
{
    bool success = true;
    bool isquit = false;
    bool media = load_media("media/red_brick.bmp");

    // load the test image background
    if(!media)
    {
        cout << "Failed to load media: " << SDL_GetError() << endl;
        success = false;
    } // if
    else // apply the image
    {
        SDL_BlitSurface(image, nullptr, window_surface, nullptr);
        SDL_UpdateWindowSurface(window);
    }


    SDL_Event test_event; // creates an event QUEUE
    while (!isquit) // quit trigger is not activated
    {
        if (SDL_PollEvent( & test_event)) // if there is an event in the event QUEUE, process
        {
            if (test_event.type == SDL_QUIT)
             {
                isquit = true;
            } // if
        } // if
    } // while

    return success;
} // Window::test_run - runs a test event