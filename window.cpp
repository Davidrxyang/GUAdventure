#include "window.h"

Window::Window()
{
    // initialize all pointers to nullptr
    renderer = nullptr;
    background = nullptr;
    temp_image = nullptr;
    window_surface = nullptr;

    set_name("default name");
    center_x = SDL_WINDOWPOS_CENTERED;
    center_y = SDL_WINDOWPOS_CENTERED;
    width = 680;
    height = 480;

    window = build_window(center_x, center_y, width, height);   
    renderer = build_renderer(window);

    if(!window)
    {
        cout << "Failed to create window: " << SDL_GetError();
    } // if
} // Window::Window default constructor             

Window::Window(string name)
{
    initialize();
    
    // initialize all pointers to nullptr
    renderer = nullptr;
    background = nullptr;
    temp_image = nullptr;
    window_surface = nullptr;
    
    set_name(name);
    center_x = SDL_WINDOWPOS_CENTERED;
    center_y = SDL_WINDOWPOS_CENTERED;
    width = 680;
    height = 480;
    
    window = build_window(center_x, center_y, width, height);
    renderer = build_renderer(window);

    if(!window)
    {
        cout << "Failed to create wcccindow: " << SDL_GetError();
    } // if
} // Window::Window explicit constructor with name

Window::Window(string name, int x, int y, int w, int h)
{
    initialize();

    // initialize all pointers to nullptr
    renderer = nullptr;
    background = nullptr;
    temp_image = nullptr;
    window_surface = nullptr;
    
    set_name(name);
    window = build_window(x, y, w, h);
    renderer = build_renderer(window);

    if(!window)
    {
        cout << "Failed to create window: " << SDL_GetError();
    } // if
} // Window::Window - explicit constructor with dimensions

void Window::set_name(string name)
{
    this -> window_name = name;
} // Window::set_name

SDL_Window* Window::build_window(int center_x, int center_y, int width, int height)
{
    const char* title = window_name.c_str();
    SDL_Window* new_window = SDL_CreateWindow(title, center_x, center_y, width, height, 0);
    
    if (new_window == nullptr)
    {
        cout << "Failed to build window: " << SDL_GetError() << endl;
        return nullptr;
    } // if
    
    return new_window;
} // Window::build_window - private function, builds window and corresponding renderer

SDL_Renderer* Window::build_renderer(SDL_Window* window)
{ 
    SDL_Renderer* new_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (new_renderer == nullptr)
    {
        cout << "Failed to create renderer: " << SDL_GetError() << endl;
    } // if

    // initialize renderer color
    SDL_SetRenderDrawColor(new_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    return new_renderer;
} // Window::build_renderer

bool Window::initialize() const // private member function
{
    bool success = true;

    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Failed to initialize SDL2 library: " << SDL_GetError() << endl;
        success = false;
    } // if

    // initialize SDL image
    int IMG_flag = IMG_INIT_PNG;
    if (!(IMG_Init(IMG_flag) & IMG_flag))
    {
        cout << "Failed to initialize SDL_image library: " << IMG_GetError() << endl;
        success = false;
    } // if

    return success;
} // Window::initialize - initializes the SDL2 library

bool Window::set_background(string media_path)
{
    bool success = true;
    background = load_texture(media_path);
    if (background == nullptr)
    {
        cout << "Failed to load background: " << SDL_GetError() << endl;
        cout << "background image path: " << media_path << endl;
        success = false;
    } // if

    return success;
} // Window::set_background

bool Window::load_media()
{
    bool success = true;
    
    KeyPress[key_default] = load_surface("media/coke.png");
    if (KeyPress[key_default] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_up] = load_surface("media/jack.png");
    if (KeyPress[key_up] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_down] = load_surface("media/fish.png");
    if (KeyPress[key_down] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_left] = load_surface("media/hotdog.png");
    if (KeyPress[key_left] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_right] = load_surface("media/potato.png");
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
    SDL_Surface* loaded_surface = IMG_Load(media_path.c_str());
    return loaded_surface;
} // Window::load_surface - TODO implement optimize option, fine for now

SDL_Texture* Window::load_texture(string media_path)
{
    SDL_Texture* loaded_texture = nullptr;
    SDL_Surface* loaded_surface = load_surface(media_path);

    if (loaded_surface == nullptr)
    {
        cout << "Failed to load image: " << IMG_GetError() << endl;
        cout << "Image path: " << media_path << endl;
    } // if
    else
    {
        // make a texture from the loaded surface
        loaded_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (loaded_texture == nullptr)
        {
            cout << "Failed to create texture from surface: " << SDL_GetError() << endl;
        } // if

        // deallocate temporary loaded surface
        SDL_FreeSurface(loaded_surface);
    }
    return loaded_texture; // if failed returns nullptr
} // Window::load_texture

void Window::close_window()
{

	for (size_t i = 0; i < key_total; ++i)
	{
		SDL_FreeSurface( KeyPress[i] );
		KeyPress[i] = nullptr;
	}

    SDL_DestroyTexture(background);
    background = nullptr;

    // frees allocated image surface
    SDL_FreeSurface(temp_image);
    temp_image = nullptr;

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

    // calls explicit name constructor for window 

    // load the background
    if (!set_background("media/red_brick.png"))
    {
        cout << "Failed to load background: " << SDL_GetError() << endl;
        success = false;
    } // if

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
                    } // SWITCH            
                } // else if - event keydown 

            // after poll for event, render texture 

            // temporary SDL rectangle for image dimensions
            rect.x = 0;
            rect.y = 0;
            rect.w = 100;
            rect.h = 100;
    
            texture = SDL_CreateTextureFromSurface(renderer, temp_image);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, background, nullptr, nullptr); // background
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
            SDL_RenderPresent(renderer);
        
            } // if - there is an event in the event queue
        } // while CLOSES MAIN LOOP
    } // else

    // close_window(); // deallocate surfaces, in case of C undefined behavior

    return success;
} // Window::test_run - runs a test event