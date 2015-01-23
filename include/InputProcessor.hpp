#ifndef INPUT_PROCESSOR_HPP
#define INPUT_PROCESSOR_HPP

#include <SDL2/SDL.h>
#include "Vector.hpp"

class InputProcessor
{
    public:
        InputProcessor () { ; }
        virtual ~InputProcessor () { ; }

        virtual void process_event (SDL_Event *e);

        virtual Uint32 handle_input (SDL_Event *e);

        /// Returns vector to mouse position
        static const Vector2D<int> mouse_position();
};

#endif // INPUT_PROCESSOR_HPP
