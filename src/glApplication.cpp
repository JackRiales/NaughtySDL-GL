#include "glApplication.hpp"
using namespace ngl;

// CONSTRUCTION AND INITIALIZATION ////////////////////////////////////////////
glApplication::glApplication (/*Uint8 glMajorVersion, Uint8 glMinorVersion,*/ std::string header, unsigned int width, unsigned int height):
_running(true),    // Running will always be set to true
// Initialize window attributes
_width  (width),    // Width is initialized
_height (height),   // Height is initialized
_header (header),   // Header is initialized
// Initialize graphics program
_programID              (0), // Program ID is unbound to start
_vertexPos2DLocation    (-1),
_vbo                    (0),
_ibo                    (0)
{
    // Window and GL context are initialized.
    if (!initialize(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION))
    {
        // Things didn't work. Destroy the window and quit.
        free();
        quit();
    }
}

glApplication::~glApplication()
{
    free();
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
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

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
                //Initialize GLEW
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if( glewError != GLEW_OK )
                {
                    glewLogError("Error initializing GLEW.", glewError);
                }

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
                } // Finished GL Initialization
            } // Finished context
        } // Finished window
    } // Finished SDL init
    return true;
}

const bool glApplication::glInitialize(void)
{
    #if GL_2_1 // OpenGL 2.1 initialization is invalid for 3.1
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

    // Set up an orthographic perspective, for 2D
    glOrtho (
            0.0,            // left
            screen_width(), // right
            screen_height(),// bottom
            0.0,            // top
            -1.0,           // zNear
            1.0             // zFar
            );

    // Error check
    if (glErrorCheck("Error initializing the projection matrix.", error))
        return false;

    // If all is well, set the clear color
    glClearColor (0.f, 0.f, 0.f, 1.f);

    // One final error check, just to be safe
    if (glErrorCheck("Error initializing OpenGL clear color.", error))
        return false;

    return true;
    #else
    // OpenGL 3.1 Initialization using graphics and shader programs

    // Start by setting the program ID
    _programID = glCreateProgram();

    // Create a vertex shader
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);

    // Write vertex shader source code
    const GLchar* vertexShaderSource[] =
    {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };

    // Set the vertex source
    glShaderSource(vert_shader, 1, vertexShaderSource, NULL);

    // Compile the vertex source
    glCompileShader(vert_shader);

    // Error check
    GLint shader_compiled = GL_FALSE;
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &shader_compiled);
    if (shader_compiled != GL_TRUE)
    {
        printf ("Unable to compile vertex shader %d.\n", vert_shader);
        // printShaderLog(vert_shader);
        return false;
    }

    // If vertex shader compiled,
    else
    {
        // Attach the shader to the program
        glAttachShader(_programID, vert_shader);

        // Create fragment shader
        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        // Write fragment shader source
        const GLchar* fragmentShaderSource[] =
        {
            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
        };

        // Set fragment source
        glShaderSource( fragment_shader, 1, fragmentShaderSource, NULL );

        // Compile fragment source
        glCompileShader( fragment_shader );

        // Error check
        GLint shader_compiled_frag = GL_FALSE;
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &shader_compiled_frag);
        if (shader_compiled != GL_TRUE)
        {
            printf ("Unable to compile fragment shader %d.\n", fragment_shader);
            // printShaderLog(vert_shader);
            return false;
        }

        // If compilation was successful,
        else
        {
            // Attach the fragment shader
            glAttachShader (_programID, fragment_shader);

            // Link the program
            glLinkProgram(_programID);

            // Check for errors
            GLint program_success = GL_TRUE;
            glGetProgramiv(_programID, GL_LINK_STATUS, &program_success);
            if (program_success != GL_TRUE)
            {
                printf ("Error linking program %d.\n", _programID);
                // printProgramLog(_programID);
                return false;
            }
            else
            {
                // Get the vertex attribute location
                _vertexPos2DLocation = glGetAttribLocation(_programID, "LVertexPos2D");

                // If it still equals -1,
                if (_vertexPos2DLocation == -1)
                {
                    printf ("LVertexPos2D is not a valid glsl program variable.\n");
                    return false;
                }
                else
                {
                    // State the clear color. (black)
                    glClearColor(0.f, 0.f, 0.f, 1.f);

                    //VBO data
                    GLfloat vertexData[] =
                    {
                        -0.5f, -0.5f,
                         0.5f, -0.5f,
                         0.5f,  0.5f,
                        -0.5f,  0.5f
                    };

                    //IBO data
                    GLuint indexData[] = { 0, 1, 2, 3 };

                    // Create the vbo
                    glGenBuffers (1, &_vbo);
                    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
                    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

                    // Create the ibo
                    glGenBuffers(1, &_ibo);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexData, GL_STATIC_DRAW);

                }
            }
        }
    }
    return true;
    #endif
}

// MAIN //////////////////////////////////////////////////////////////////////
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

            // Handle any key-based events
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

    //Bind program
        glUseProgram( _programID );

        //Enable vertex position
        glEnableVertexAttribArray( _vertexPos2DLocation );

        //Set vertex data
        glBindBuffer( GL_ARRAY_BUFFER, _vbo );
        glVertexAttribPointer( _vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

        //Set index data and render
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibo );
        glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

        //Disable vertex position
        glDisableVertexAttribArray( _vertexPos2DLocation );

        //Unbind program
        glUseProgram( NULL );
}

void glApplication::quit(void)
{
    _running = false;
}

void glApplication::free(void)
{
    // Clean up the window and destroy it
    SDL_DestroyWindow(_sdl_window);
    _sdl_window = NULL;

    // Quit SDL state
    SDL_Quit();
}

// LOGGING AND ERROR CHECKING ////////////////////////////////////////////////
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
    strcat(str, " GL Error: %s\n");
    printf( str, gluErrorString(error) );
}

void glApplication::glewLogError(std::string message, const GLenum& error)
{
    char str [80];
    strcat(str, message.c_str());
    strcat(str, " GLEW Error: %s\n");
    printf( str, glewGetErrorString(error) );
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
