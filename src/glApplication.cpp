#include "glApplication.hpp"
using namespace ngl;

/// CONSTRUCTION AND INITIALIZATION ////////////////////////////////////////////
glApplication::glApplication (Uint8 glMajorVersion, Uint8 glMinorVersion, std::string header, unsigned int width, unsigned int height):
_width  (width),    // Width is initialized
_height (height),   // Height is initialized
_header (header),   // Header is initialized
_running (true)     // Running will always be set to true
{
    // Window and GL context are initialized.
    initialize(glMajorVersion, glMinorVersion);
}

glApplication::~glApplication()
{
    // Clean up the window and destroy it
    SDL_DestroyWindow(_sdl_window);
    _sdl_window = NULL;

    // Quit SDL state
    SDL_Quit();
}

const bool glApplication::initialize(Uint8 glMajorVersion, Uint8 glMinorVersion)
{
    // Begin by performing SDL initialization. Error check.
    // <TEMP> we are initializing video only.
    if (SDL_Init ( SDL_INIT_VIDEO ) < 0)
    {
        logError ("Could not initialize SDL.");
        return false;
    }

    // If SDL initializes, begin window creation
    else
    {
        // Set context version
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, glMajorVersion );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, glMinorVersion );

        // Create the window
        _sdl_window = SDL_CreateWindow
        (
            _header.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            _width,
            _height,
            SDL_WINDOW_OPENGL |
            SDL_WINDOW_SHOWN
        );

        // Error check
        if (_sdl_window == NULL)
        {
            logError ("Window could not be created.");
            return false;
        }

        // If the window was created successfully, begin initializing the context
        else
        {
            // Instantiate the context from the window
            _glContext = SDL_GL_CreateContext( _sdl_window );

            // Error check
            if (_glContext == NULL)
            {
                logError ("OpenGL context could not be created.");
                return false;
            }

            else
            {
                // Set the swap interval to one to activate vsync. Error check, but do not return false if vsync fails.
                if ( SDL_GL_SetSwapInterval(1) < 0 )
                {
                    logError ("Warning: V-Sync failed to initialize.");
                }

                // Finally, call initGL and error check
                if ( !glInitialize() )
                {
                    printf ("Unable to initialize OpenGL.\n");
                    return false;
                } // InitGL
            } // Finished context
        } // Finished window
    } // Finished SDL init
    return true;
}

const bool glApplication::glInitialize(void)
{
    // GL Error check object
    GLenum error = GL_NO_ERROR;

    // Initialize the projection matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    // Check if that caused an error
    if (glErrorCheck("Error initializing the projection matrix.", error))
        return false;

    // Initialize the modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Error check
    if (glErrorCheck("Error initializing the projection matrix.", error))
        return false;

    // If all is well, set the clear color
    glClearColor (0.f, 0.f, 0.f, 1.f);

    // One final error check, just to be safe
    if (glErrorCheck("Error initializing OpenGL clear color.", error))
        return false;

    return true;
}

/// MAIN //////////////////////////////////////////////////////////////////////

int glApplication::main_loop( void )
{
    // Start allowing SDL to take text input
    SDL_StartTextInput();

    while (_running)
    {
        while (SDL_PollEvent(&_sdl_event) != 0)
        {
            // User quits
            if (_sdl_event.type == SDL_QUIT)
            {
                _running = false;
                break;
            }
            else if ( _sdl_event.type == SDL_TEXTINPUT )
            {
                handle_key_input(_sdl_event.text.text[0]);
            }
        }

        // Render the buffer
        render();

        // Swap the buffer
        SDL_GL_SwapWindow(_sdl_window);
    }

    // Stop the input
    SDL_StopTextInput();

    return 0;
}

void glApplication::handle_key_input(unsigned char key)
{
    // Escape key is keycode 27
    if (key == 27)
    {
        _running = false;
    }
}

void glApplication::update( void )
{
    ; // Nothing yet
}

void glApplication::render( void )
{
    // Clear the buffer
    glClear (GL_COLOR_BUFFER_BIT);

    // Draw testing; simple quad
    #define test
    #ifdef test
    glBegin( GL_QUADS );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f( 0.5f, -0.5f );
        glVertex2f( 0.5f, 0.5f );
        glVertex2f( -0.5f, 0.5f );
    glEnd();
    #endif // test
}

/// LOGGING AND ERROR CHECKING ////////////////////////////////////////////////
void glApplication::logError(std::string message)
{
    char str [80];
    strcat(str, message.c_str());
    strcat(str, " SDL Error: %s\n");
    printf( str, SDL_GetError() );
}

void glApplication::glLogError(std::string message, const GLenum& error)
{
    char str [80];
    strcat(str, message.c_str());
    strcat(str, " SDL Error: %s\n");
    printf( str, gluErrorString(error) );
}

bool glApplication::glErrorCheck(std::string message, GLenum& error)
{
    error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        glLogError(message, error);
        return true;
    }
    return false;
}
