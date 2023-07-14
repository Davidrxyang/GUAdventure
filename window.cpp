#include "window.h"

Window::Window()
{
    // initialize all pointers to nullptr
    renderer = nullptr;
    background = nullptr;
    temp_image = nullptr;
    window_surface = nullptr;

    set_name("default name");
    set_font("assets/fonts/default_font.ttf", 30, 0, 0, 0);
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

    set_font("assets/fonts/default_font.ttf", 30, 0, 0, 0);
    set_name(name);
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
} // Window::Window explicit constructor with name

Window::Window(string name, int x, int y, int w, int h)
{
    initialize();

    // initialize all pointers to nullptr
    renderer = nullptr;
    background = nullptr;
    temp_image = nullptr;
    window_surface = nullptr;
    
    set_font("assets/fonts/default_font.ttf", 30, 0, 0, 0);
    set_name(name);
    center_x = x;
    center_y = y;
    width = w;
    height = h;
    window = build_window(x, y, w, h);
    renderer = build_renderer(window);

    if(!window)
    {
        cout << "Failed to create window: " << SDL_GetError();
    } // if   
} // Window::Window explicit constructor with dimensions

Window::Window(string name, int x, int y, int w, int h, string font_path, int font_size)
{
    initialize();

    // initialize all pointers to nullptr
    renderer = nullptr;
    background = nullptr;
    temp_image = nullptr;
    window_surface = nullptr;
    
    set_name(name);
    set_font(font_path, font_size, 0xFF, 0xFF, 0xFF);
    center_x = x;
    center_y = y;
    width = w;
    height = h;
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

void Window::set_font(string font_path, int font_size, Uint8 r, Uint8 g, Uint8 b)
{
    font = TTF_OpenFont(font_path.c_str(), font_size);
    if (font == nullptr)
    {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    } // if
    SDL_Color color = {0,0,0};
    font_color = color;
} // Window::set_font

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

void Window::set_local_text(string text)
{
    text_texture = load_from_rendered_text(text.c_str(), font_color);
} // Window::set_local_text

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
    // create VSYNCed renderer for window
    SDL_Renderer* new_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

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

    // initialize SDL true type fonts (TTF)
    if (TTF_Init() == -1)
    {
        cout << "Failed to initialize SDL_ttf library: " << TTF_GetError() << endl;
        success = false;
    } // if

    return success;
} // Window::initialize - initializes the SDL2 libraries

bool Window::load_media()
{
    bool success = true;
    
    KeyPress[key_default] = load_surface("assets/assets/media/coke.png");
    if (KeyPress[key_default] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_up] = load_surface("assets/media/jack.png");
    if (KeyPress[key_up] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_down] = load_surface("assets/media/fish.png");
    if (KeyPress[key_down] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_left] = load_surface("assets/media/hotdog.png");
    if (KeyPress[key_left] == nullptr)
    {
        cout << "Failed to load image: " << SDL_GetError() << endl;
        success = false;
    } // if

    KeyPress[key_right] = load_surface("assets/media/potato.png");
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

SDL_Texture* Window::load_texture(string media_path, Uint8 key_r, Uint8 key_g, Uint8 key_b)
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
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface -> format, key_r, key_g, key_b));
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
} // Window::load_texture - with RGB color key input

SDL_Texture* Window::load_from_rendered_text(string text, SDL_Color text_color)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
    SDL_Texture* text_texture = nullptr;

    if (text_surface == nullptr)
    {
        cout << "Failed to load text: " << TTF_GetError() << endl;
    } // if
    else
    {
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (text_texture == nullptr)
        {
            cout << "Failed to create text from surface: " << TTF_GetError() << endl;
        } // if
    } // else
    SDL_FreeSurface(text_surface); 
    return text_texture;
} // Window::load_from_rendered_text

SDL_Texture* Window::texture_from_surface(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(renderer, surface);
} // Window::texture_from_surface

SDL_Texture* Window::texture_from_surface(SDL_Surface* surface, Uint8 key_r, Uint8 key_g, Uint8 key_b)
{
    SDL_Texture* temp_texture = nullptr;
    if (surface != nullptr)
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface -> format, key_r, key_g, key_b));
    } // if surface is null, directly return without setting color key
    temp_texture = SDL_CreateTextureFromSurface(renderer, surface);

    return temp_texture;
} // Window::texture_from_surface

void Window::render(SDL_Texture* texture) const
{
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
} // Window::render

void Window::render(SDL_Texture* texture, SDL_Rect* rect) const
{
    SDL_RenderCopy(renderer, texture, nullptr, rect);
} // Window::render - with rect specification

void Window::render(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* clip) const
{
    SDL_RenderCopy(renderer, texture, clip, rect);
} // Window::render - with rect specs and clip rendering for sprite sheet functionality

void Window::render(SDL_Texture* texture, SDL_Rect* rect, SDL_Rect* clip, double rotate_angle,
                    SDL_Point* rotate_center, SDL_RendererFlip flip) const
{
    SDL_RenderCopyEx(renderer, texture, clip, rect, rotate_angle, rotate_center, flip);
} // Window::render - above, with rotation specs

void Window::render_clear() const
{
    SDL_RenderClear(renderer);
} // Window::render_clear

void Window::update_screen() const
{
    SDL_RenderPresent(renderer);
} // Window::update_screen

void Window::modulate_color(SDL_Texture* texture, Uint8 r, Uint8 g, Uint8 b) const
{
    SDL_SetTextureColorMod(texture, r, g, b);
} // Window::modulate_color

void Window::modulate_alpha(SDL_Texture* texture, Uint8 alpha) const
{
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); // enables blending
    SDL_SetTextureAlphaMod(texture, alpha); // alpha blending - TRANSPARENCY OF TEXTURE
} // Window::modulate_alpha

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




bool Window::test_run_1()
{
    bool success = true;
    bool isquit = false;

    // calls explicit name constructor for window 

    // load the background
    if (!set_background("assets/media/red_brick.png"))
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
            
            texture = texture_from_surface(temp_image, 0xFF, 0xFF, 0xFF);
            
            render_clear();

            render(background);
            render(texture, &rect);
            update_screen();

            } // if - there is an event in the event queue
        } // while CLOSES MAIN LOOP
    } // else

    // close_window(); // deallocate surfaces, in case of C undefined behavior

    return success;
} // Window::test_run - runs a test event
