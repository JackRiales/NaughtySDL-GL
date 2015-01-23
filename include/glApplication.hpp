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
            \param OpenGL version is (2.1) by default.
            \param Window header is "Naughty SDL-GL Application" by default.
            \param Resolution is 800x600 by default.
        */

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

        ~glApplication();
        /**
            \name Destructor.
            \brief Deallocates window memory.
        */

    protected:
        const virtual bool initialize(Uint8, Uint8);
        /**
            \name Initializer.
            \brief Called in the constructor to instantiate window and GL context.
            \param Entries are the OpenGL context version passed from the constructor.
            \return true if all instantiated correctly. Write to log success notification.
            \return false if a component failed. Write to log when this happens.
        */

    private:
        /// Window attributes
        SDL_Window*     _sdl_window;/// Actual SDL window.
        unsigned int    _width,     /// Width of the window.
                        _height;    /// Height of the window.
        std::string     _header;    /// Window header.

        /// GL attributes
        Uint8           _glMajor,   /// OpenGL major version. Must be valid.
                        _glMinor;   /// OpenGL minor version. Must be valid.
        SDL_GLContext   _glContext; /// SDL's gl context object.
        bool            _running;   /// Flag to determine when the program continues to run.
};

}

#endif // _N_GL_APPLICATION_HPP
