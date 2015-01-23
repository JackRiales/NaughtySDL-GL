#ifndef COLOR_HPP
#define COLOR_HPP

#include <SDL/SDL.h>

struct Color
{
    Color (Uint8 red = 0x0, Uint8 green = 0x0, Uint8 blue = 0x0, Uint8 alpha = 0xFF) :
    r (red), g (green), b (blue), a (alpha) {   ;   }

    Uint8   r;
    Uint8   g;
    Uint8   b;
    Uint8   a;
};

#endif // COLOR_HPP
