#ifndef SPRITE_UPDATER_HPP
#define SPRITE_UPDATER_HPP

#include "InputProcessor.hpp"
#include "Sprite.hpp"

class SpriteUpdater : public InputProcessor
{
    public:
        SpriteUpdater(Sprite* host): _host (host) {;}
        ~SpriteUpdater() {;}

        virtual void process_event (SDL_Event *e) override
        {
            while (SDL_PollEvent( e ) != 0)
            {
                if (e->type != SDL_QUIT)
                {
                    e->type = handle_input(e);
                }
            }
        }

        virtual Uint32 handle_input (SDL_Event *e) override
        {
            if (e->type == SDL_KEYDOWN)
            {
                /// Move host left and right
                switch( e->key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                        return SDL_QUIT;
                        break;
                    case SDLK_a:
                        _host->set_rotation (_host->rotation() - 1.0);
                        _host->set_position (_host->position().x - 1, _host->position().y);
                        break;
                    case SDLK_d:
                        _host->set_rotation (_host->rotation() + 1.0);
                        _host->set_position (_host->position().x + 1, _host->position().y);
                        break;
                }
            }

            /// Click to move host
            else if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                printf ("Sprite will now shift to mouse position (%d, %d)\n", mouse_position().x, mouse_position().y);
                _host->set_position(mouse_position().x - _host->origin()->x, mouse_position().y - _host->origin()->y);
            }

            /// Default state return
            return SDL_SYSWMEVENT;
        }

    private:
        Sprite* _host;
};

#endif // SPRITE_UPDATER_HPP
