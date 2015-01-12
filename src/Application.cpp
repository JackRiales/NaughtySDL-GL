#include "Application.hpp"

Application::Application(const std::string& header, const unsigned int& width, const unsigned int& height, const bool& begin_immediately) :
_window (NULL),
_screen (NULL),
_renderer (NULL),
_header (header),
_width (width),
_height (height),
_running (true)
{
    // Initialize and begin
    if (initialize()) {
        if (begin_immediately) {
            main_loop();
        }
    }
}

Application::~Application()
{
    // Release window memory before formally exiting
    exit();
}

void Application::main_loop(InputProcessor *input)
{
    while (_running)
    {
        /// Input based procession
        if (input != NULL)
        {
            input->process_event(&_event);
            if (_event.type == SDL_QUIT)
            {
                _running = false;
            }
        }
        else
        {
            /// Default event procession
            while (SDL_PollEvent(&_event) != 0)
            {
                if (_event.type == SDL_QUIT)
                {
                    _running = false;
                }
            }
        }

        render();
    }
}

void Application::add_render_node(IRenderNode& node)
{
    printf ("Mounting renderable on layer %i\n", node.layer());
    _render_nodes.push_back ( &node );
}

bool Application::initialize()
{
    printf ("Beginning initialization...\n");
    // Perform initialization, and error check
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    else
    {
        // Create window window
        printf ("Creating render window...\n");
        _window = SDL_CreateWindow
        (
            _header.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            _width,
            _height,
            SDL_WINDOW_SHOWN
        );

        // Error check window creation
        if (_window == NULL)
        {
            printf( "SDL window could not initialize! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }
        else
        {
            // Set window screen surface
            _screen = SDL_GetWindowSurface( _window );

            // Initialize renderer, as well. Error check.
            printf ("Initializing renderer...\n");
            _renderer = SDL_CreateRenderer( _window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (_renderer == NULL)
            {
                printf ("Renderer device could not initialize! SDL_Error: %s\n", SDL_GetError());
                return false;
            }

            // Since we're using SDL_Image, we must initialize it as well.
            printf ("Initializing IMG...\n");
            int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
            if ( !(IMG_Init(imgFlags) & imgFlags) )
            {
                printf ("SDL_Image could not be initialized. SDL_Image Error: %s\n", IMG_GetError());
                return false;
            }
        }
    }
    return true;
}

void Application::render()
{
    SDL_SetRenderDrawColor(_renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(_renderer);

    for (unsigned int LAYER = 0; LAYER <= layer_max(); LAYER++)
    {
        for (std::vector<IRenderNode*>::iterator it = _render_nodes.begin(); it != _render_nodes.end(); ++it)
        {
            if ( (*it)->layer() == LAYER )
            {
                (*it)->render (_renderer);
            }
        }
    }

    SDL_RenderPresent(_renderer);
}

void Application::exit()
{
    SDL_DestroyWindow( _window );
    SDL_DestroyRenderer( _renderer );
    _window = NULL;
    _renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

const unsigned int Application::layer_max()
{
    unsigned int layer = 0;
    for (std::vector<IRenderNode*>::iterator it = _render_nodes.begin(); it != _render_nodes.end(); ++it)
    {
        if ( (*it)->layer() > layer )
        {
            layer = (*it)->layer();
        }
    }
    return layer;
}
