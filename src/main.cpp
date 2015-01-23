/// Inclusion macros
#include <random>
#include <ctime>
#include "NaughtySDL.hpp"
#include "Geometry.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "AnimatedSprite.hpp"
#include "Testing/SpriteUpdater.hpp"
#include "Text.hpp"

/// Testing definitions, comment / uncomment as needed
#define _TEST_GEOMETRY
#define _TEST_SPRITES
#define _TEST_TEXT
#define _TEST_INPUT

/// Test main method
int main (int argc, char** argv)
{
    const int width = 800;
    const int height = 800;
    Naughty_Init ("NaughtySDL Testing Program", width, height);

    #ifdef _TEST_GEOMETRY
    srand (time (NULL));
    const int box_size = 10;
    const int box_count_x = width / box_size;   // 80
    const int box_count_y = height / box_size;  // 80

    Geometry2D boxes [ box_count_x ][ box_count_y ];

    int current_x_pos = 0;
    int current_y_pos = 0;
    for (int x = 0; x < box_count_x; x++)
    {
        for (int y = 0; y < box_count_y; y++)
        {
            Geometry2D _current (current_x_pos, current_y_pos, box_size, box_size);
            _current.set_color( rand() % 255, rand() % 255, rand() % 255, 255 );
            boxes [x][y] = _current;

            Naughty_MountRenderable( boxes[x][y] );

            current_y_pos += box_size;
        }
        current_x_pos += box_size;
    }
    #endif // _TEST_GEOMETRY

    #ifdef _TEST_SPRITES
    SDL_Point center = { 45, 45 };
    Transform2D trans (*new iVector2D(50, 50), 0.0, &center);
    Sprite sprite
    (
        new Texture (Naughty_MainRenderer, "Resources/logo.png", NULL),
        NULL,
        &trans
    );

    Naughty_MountRenderable(sprite);
    #endif // _TEST_SPRITES

    #ifdef _TEST_TEXT
    Text helloWorld (Naughty_MainRenderer, "Resources/fixedsys.ttf", "Hello, World!", *new Transform2D(0,0), 48, *new Color(255, 255, 255));
    Naughty_MountRenderable(helloWorld);
    #endif

    #if defined (_TEST_INPUT) && defined (_TEST_SPRITES)
    return Naughty_Run(new SpriteUpdater(&sprite));
    #else
    return Naughty_Run();
    #endif
}
