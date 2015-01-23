#include "InputProcessor.hpp"

void InputProcessor::process_event(SDL_Event *e)
{
    while (SDL_PollEvent( e ) != 0)
    {
        if (e->type != SDL_QUIT)
        {
            e->type = handle_input(e);
        }
    }
}


Uint32 InputProcessor::handle_input(SDL_Event *e)
{
    // Check if a key is being pressed
    if (e->type == SDL_KEYDOWN)
    {
        // Check if the key is the escape key
        if (e->key.keysym.sym == SDLK_ESCAPE)
        {
            // Change the event's flag to quit
            return SDL_QUIT;
        }
    }
    return SDL_SYSWMEVENT;
}

const Vector2D<int> InputProcessor::mouse_position()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return (*new Vector2D<int>(x, y));
}
