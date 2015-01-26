/**
    Jack Riales
    SDL-GL Application Class
    Priorities:
        - Open and maintain SDL window
        - Begin OpenGL context
        - Initialize OpenGL
        - Handle key input
        - Update logic
        - Draw

    Dependencies:
        - SDL2
        - GLU
        - Standard IO
        - STL String
*/

#ifndef _N_GL_APPLICATION_HPP
#define _N_GL_APPLICATION_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string>

namespace ngl
{

class glApplication
{
    public:
        /// Default OpenGL version is 3.1
        static const Uint8 OPENGL_MAJOR_VERSION = 3;
        static const Uint8 OPENGL_MINOR_VERSION = 1;

        glApplication
        (
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

        void quit ( void );
        /**
            \name Quit
            \brief Sets _running to false, flagging the end of the program.
        */

    protected:
        const bool initialize(Uint8, Uint8);
        /**
            \name Initializer.
            \brief Called in the constructor to instantiate window and GL context.
            \param Uint8 OpenGL context version passed from the constructor.
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

        void free (void);
        /**
            \name Free
            \brief Deallocates memory for window and quits SDL state
        */

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

        static void glewLogError(std::string, const GLenum&);
        /**
            \name GlewLogError
            \brief Logs a glew error to console with the given message.
            \param string The message to send with the error.
            \param GLenum enumerated error value.
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

    private:
        bool            _running;   ///< Flag to determine when the program continues to run.

        /// Window attributes
        SDL_Window*     _sdl_window;///< Actual SDL window.
        SDL_Event       _sdl_event; ///< SDL Window Event Handler
        unsigned int    _width,     ///< Width of the window.
                        _height;    ///< Height of the window.
        std::string     _header;    ///< Window header.

        /// GL attributes
        SDL_GLContext   _glContext; ///< SDL's gl context object.

        /// Graphics Program Attributes
        GLuint          _programID; ///< Program ID
        GLuint          _vertexPos2DLocation;
        GLuint          _vbo;       ///< Vertex Buffer Objects
        GLuint          _ibo;       ///< Index Buffer Objects

    /// Accessors
    public:
        /// Return the current width of the screen
        inline const unsigned int& screen_width (void) const { return _width; }

        /// Return the current height of the screen
        inline const unsigned int& screen_height(void) const { return _height;}
};

}

#endif // _N_GL_APPLICATION_HPP
