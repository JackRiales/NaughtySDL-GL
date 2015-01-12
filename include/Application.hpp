/**
    Application Class
    - Creates and operates the main render window
*/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <stdio.h>
#include <vector>

#include "InputProcessor.hpp"
#include "RenderNode.hpp"

class Application
{
    public:
        Application
        (const std::string& header = "Naughty SDL Application",
         const unsigned int& width = 640,
         const unsigned int& height = 480,
         const bool& begin_immediately = false);
        /**
            Constructor.
            Initializes SDL state (all subsystems) and begins a main window event loop.
        */

        virtual ~Application ();
        /**
            Destructor.
            Releases window memory before exiting.
        */

        virtual void main_loop(InputProcessor *input = new InputProcessor);
        /**
            Main window event loop method, with inclusion of an input processor.
            - Polls window event
            - Takes input, handles based on processor
            - Updates window surface
        */

        void add_render_node (IRenderNode& node);
        /**
            Render node insertion method.
            Adds the address of an object that needs to be rendered on screen.
        */

    protected:
        virtual bool initialize();
        /**
            SDL initialization method.
            - Initializes SDL state
            - Creates window
            - Sets main window surface
            - Performs initial error checking and return false if any errors are found.
        */

        virtual void render();
        /**
            Main loop render method
            - Calls the renderer to clear and present to the window.
        */

        virtual void exit();
        /**
            Exit method.
            - Releases window memory.
        */

    private:
        SDL_Window*     _window;
        SDL_Surface*    _screen;
        SDL_Renderer*   _renderer;
        SDL_Event       _event;
        std::string     _header;
        unsigned int    _width;
        unsigned int    _height;
        bool            _running;
        std::vector<IRenderNode*> _render_nodes;

    /// Accessors
    public:
        inline SDL_Renderer* renderer() { return _renderer; }
        inline const unsigned int& width() { return _width; }
        inline const unsigned int& height(){ return _height; }
        const unsigned int layer_max ();
};

#endif // APPLICATION_HPP
