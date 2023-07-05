#include "window.h"

Window::Window()
{
    set_name("default name");
    center_x = SDL_WINDOWPOS_CENTERED;
    center_y = SDL_WINDOWPOS_CENTERED;
    width = 680;
    height = 480;

    window = build_window(center_x, center_y, width, height);   

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
    
    set_name(name);
    center_x = SDL_WINDOWPOS_CENTERED;
    center_y = SDL_WINDOWPOS_CENTERED;
    width = 680;
    height = 480;

    window = build_window(center_x, center_y, width, height);
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
    set_name(name);
    window = build_window(x, y, w, h);
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

void Window::set_name(string name)
{
    this -> window_name = name;
} // Window::set_name

SDL_Window* Window::build_window(int center_x, int center_y, int width, int height)
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

bool Window::load_media()
{
    bool success = true;

    KeyPress[key_default] = load_surface("media/coke.bmp");
    if (KeyPress[key_default] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_up] = load_surface("media/jack.bmp");
    if (KeyPress[key_up] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_down] = load_surface("media/fish.bmp");
    if (KeyPress[key_down] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_left] = load_surface("media/hotdog.bmp");
    if (KeyPress[key_left] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_right] = load_surface("media/potato.bmp");
    if (KeyPress[key_right] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    return success;
} // Window::load_media

bool Window::load_media(string media_path)
{
    bool success = true;

    temp_image = load_surface(media_path);
    
    return success;
} // Window::load_media

SDL_Surface* Window::load_surface(string media_path)
{
    return load_surface(media_path, true);
} // Window::load_surface

SDL_Surface* Window::load_surface(string media_path, bool optimized)
{
    SDL_Surface* optimized_surface = nullptr;
    SDL_Surface* loaded_surface = SDL_LoadBMP(media_path.c_str());
    if (loaded_surface == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        cout << "Image path: " << media_path << endl;
    } // if
    else if (optimized)
    {
        //converting format
        optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface -> format, 0);

        if (optimized_surface == nullptr)
        {
            cout << "Unable to optimize surface: " << SDL_GetError() << endl;
            cout << "Image path: " << media_path << endl;
        } // if
        SDL_FreeSurface(loaded_surface); // destroy unused surface
        return optimized_surface;
    } // else if
    else
    {
        return loaded_surface;
    } // else
    return loaded_surface;
} // Window::load_surface

void Window::close_window()
{

	for (size_t i = 0; i < key_total; ++i)
	{
		SDL_FreeSurface( KeyPress[i] );
		KeyPress[i] = nullptr;
	}
    // frees allocated image surface
    SDL_FreeSurface(temp_image);
    temp_image = nullptr;

    SDL_FreeSurface(background);
    background = nullptr;
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

    bool load_background = load_media("media/red_brick.bmp");

    // load the background
    if (!load_background)
    {
        cout << "Failed to load background: " << SDL_GetError() << endl;
        success = false;
    } // if
    else // apply background
    {
        background = temp_image; // set the background
        SDL_BlitSurface(background, nullptr, window_surface, nullptr);
        SDL_UpdateWindowSurface(window);
    } // else

    // loading default media

    if (!load_media())
    {
        cout << "Failed to load default media: " << SDL_GetError() << endl;
        success = false;
    }

    else
    {

        // THIS IS THE MAIN LOOP 

        SDL_Event test_event; // creates an event QUEUE
        while (!isquit) // quit trigger is not activated
        {
            if (SDL_PollEvent( & test_event)) // if there is an event in the event QUEUE, process
            {
                if (test_event.type == SDL_QUIT)
                {
                    isquit = true;
                } // if
                else if (test_event.type == SDL_KEYDOWN)
                {
                    // a key has been pressed
                    switch(test_event.key.keysym.sym)
                    {
                        case SDLK_UP:
                        temp_image = KeyPress[key_up];
                        break;

                        case SDLK_DOWN:
                        temp_image = KeyPress[key_down];
                        break;

                        case SDLK_LEFT:
                        temp_image = KeyPress[key_left];
                        break;

                        case SDLK_RIGHT:
                        temp_image = KeyPress[key_right];
                        break;

                        case SDLK_q: // quits the loop 
                        isquit = true;
                        break;

                        default:
                        temp_image = KeyPress[key_default];
                        break;
                    }                
                }
                SDL_BlitSurface(temp_image, nullptr, window_surface, nullptr);
                SDL_UpdateWindowSurface(window);
                // updates the surface
            } // if
        } // while CLOSES MAIN LOOP
    } // else

    // close_window(); // deallocate surfaces, in case of C undefined behavior

    return success;
} // Window::test_run - runs a test event