/**
    Jack Riales
    SDL-GL Application Class
    Priorities:
        - Open and maintain SDL window
        - Begin OpenGL context
*/

#ifndef _N_GL_APPLICATION_HPP
#define _N_GL_APPLICATION_HPP

/// Inclusion macros
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdio.h>
#include <string>

namespace ngl
{

class glApplication
{
    public:
        glApplication
        (
            Uint8 glMajorVersion= 2,
            Uint8 glMinorVersion= 1,
            std::string header  = "Naughty SDL-GL Application",
            unsigned int width  = 800,
            unsigned int height = 600
        );
        /**
            \name Constructor.
            \brief Initializes based on direct data from parameters.
            \param glMajorVersion OpenGL major version. 2 by default.
            \param glMinorVersion OpenGL minor version. 1 by default.
            \param Header The window header. "Naughty SDL-GL Application" by default.
            \param width The window's width. 800 by default.
            \param height The window's height. 600 by default.
        */

        #if 0   // For right now, these constructors will not work properly.
        glApplication
        (
            SDL_GLContext   glContext,
            std::string     header  = "Naughty SDL-GL Application",
            unsigned int    width   = 800,
            unsigned int    height  = 600
        );
        /**
            \name Context-Constructor
            \brief Initializes based on preexisting glContext object
        */

        glApplication
        (
            Uint8 glMajorVersion,
            Uint8 glMinorVersion,
            SDL_Window* sdl_window
        );
        /**
            \name Window-Constructor
            \brief Initializes based on given context version and a preexisting SDL_Window
        */

        glApplication
        (
            SDL_GLContext   glContext,
            SDL_Window*     sdl_window
        );
        /**
            \name Context-Window-Constructor
            \brief Initializes based on preexisting context object and preexisting SDL_Window
        */
        #endif

        ~glApplication();
        /**
            \name Destructor.
            \brief Deallocates window memory.
        */

        int main_loop ( void );
        /**
            \name Run Main Loop
            \brief Runs the main loop of the application.
            \return 0 if exited successfully.
        */

        virtual void handle_key_input ( unsigned char key );
        /**
            \name Handle Key Input
            \brief Very simple key input handler used to do very simple tasks, such as closing the window.
            \param key Key pressed.
        */

        virtual void update ( void );
        /**
            \name Update
            \brief Updates game logic.
        */

        virtual void render ( void );
        /**
            \name Render
            \brief Renders vertices to the screen.
        */

    protected:
        const bool initialize(Uint8, Uint8);
        /**
            \name Initializer.
            \brief Called in the constructor to instantiate window and GL context.
            \param Unt8 OpenGL context version passed from the constructor.
            \return true if all instantiated correctly. Write to log success notification.
            \return false if a component failed. Write to log when this happens.
        */

        const bool glInitialize(void);
        /**
            \name OpenGL State Initializer
            \brief Called during initialization to start up OpenGL
            \return True if successful
            \return False if exceptions occur
        */

    private:
        /// Window attributes
        SDL_Window*     _sdl_window;///< Actual SDL window.
        SDL_Event       _sdl_event; ///< SDL Window Event Handler
        unsigned int    _width,     ///< Width of the window.
                        _height;    ///< Height of the window.
        std::string     _header;    ///< Window header.

        /// GL attributes
        Uint8           _glMajor,   ///< OpenGL major version. Must be valid.
                        _glMinor;   ///< OpenGL minor version. Must be valid.
        SDL_GLContext   _glContext; ///< SDL's gl context object.
        bool            _running;   ///< Flag to determine when the program continues to run.

    /// Static methods
    public:
        static void logError(std::string);
        /**
            \name LogError
            \brief Logs an SDL Error message to console, along with the given message.
            \param string The message to send with the error.
        */

        static void glLogError(std::string, const GLenum&);
        /**
            \name GLLogError
            \brief Logs an OpenGL Error message to console, along with the given message.
            \param string The message to send with the error.
            \param GLenum enumerated error value
        */

        static bool glErrorCheck(std::string, GLenum&);
        /**
            \name GLErrorCheck
            \brief Checks for and logs any errors detected by OpenGL
            \return True if errors are detected
            \return False if none are detected
            \param string The message to send with the error.
            \param GLenum enumerated error value
        */
};

}

#endif // _N_GL_APPLICATION_HPP
