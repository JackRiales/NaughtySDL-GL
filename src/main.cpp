#include <random>
#include <ctime>
#include "NaughtySDL.hpp"
#include "Geometry.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "AnimatedSprite.hpp"

/// Animated sprite testing
int main (int argc, char** argv)
{
    Naughty_Init("Animated sprite testing", 800, 600);

    SDL_Rect rects[] = {
        {0, 0, 32, 32},
        {32, 32, 32, 32}
    };

    AnimatedSprite as (new Texture (Naughty_MainRenderer, "digbug.png", NULL), rects, 2);

    return Naughty_Run();
}

/// Sprite testing
/*int main (int argc, char** argv)
{
    Naughty_Init("Testing sprites", 800, 600);

    SDL_Rect draw_area = { 0, 0, 32, 32 };
    Sprite sprite (new Texture (Naughty_MainRenderer, "digbug.png", NULL),
                   draw_area,
                   0,
                   0);

    Naughty_MountRenderable(sprite);

    return Naughty_Run();
}*/

/// Texture testing
/*int main (int argc, char** argv)
{
    Naughty_Init ("Testing textures", 800, 600);

    Texture tex (Naughty_MainRenderer, "tnp.jpg", NULL, 0, 0);
    Naughty_MountRenderable(tex);

    return Naughty_Run();
}*/

/// Geometry testing
/*
int main(int argc, char** argv)
{
    srand (time (NULL));
    const int box_size = 10;
    const int width = 800;
    const int height = 800;
    const int box_count_x = width / box_size;   // 80
    const int box_count_y = height / box_size;  // 80

    Naughty_Init ("Testing Naughty Init", width, height);
    Geometry boxes [ box_count_x ][ box_count_y ];

    int current_x_pos = 0;
    int current_y_pos = 0;
    for (int x = 0; x < box_count_x; x++)
    {
        for (int y = 0; y < box_count_y; y++)
        {
            Geometry _current (current_x_pos, current_y_pos, box_size, box_size);
            _current.set_color( rand() % 255, rand() % 255, rand() % 255, 255 );
            boxes [x][y] = _current;

            Naughty_MountRenderable( boxes[x][y] );

            current_x_pos += box_size;
            current_y_pos += box_size;
        }
    }
    return Naughty_Run();
}
*/
