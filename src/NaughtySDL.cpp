#include "NaughtySDL.hpp"

Application* APP_MAIN = nullptr;

void Naughty_Init (const std::string& header, const unsigned int& width, const unsigned int& height)
{
    printf ("Initializing NaughtySDL...\n");
    APP_MAIN = new Application (header, width, height);
    printf ("NaughtySDL initialization complete.\n");
}

const int Naughty_Run (InputProcessor* input)
{
    printf ("Running main loop...\n");
    APP_MAIN->main_loop (input);
    printf ("Exiting NaughtySDL...\n");
    return 0;
}

void Naughty_MountRenderable (IRenderNode& node)
{
    APP_MAIN->add_render_node(node);
    printf ("Node mounted.\n");
}

const Vector2D <unsigned int> Naughty_CurrentResolution ()
{
    Vector2D <unsigned int> res ( APP_MAIN->width(), APP_MAIN->height() );
    return res;
}
