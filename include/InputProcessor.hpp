#ifndef INPUT_PROCESSOR_HPP
#define INPUT_PROCESSOR_HPP

#include <SDL.h>

class InputProcessor
{
    public:
        InputProcessor () { ; }
        virtual ~InputProcessor () { ; }

        virtual void process_event (SDL_Event *e);

        virtual Uint32 handle_input (SDL_Event *e);
};

#endif // INPUT_PROCESSOR_HPP
