#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <stdio.h>

#include "Vector.hpp"
#include "Color.hpp"

class Texture
{
    public:
        Texture ();
        Texture (SDL_Texture* texture);
        Texture (SDL_Renderer* renderer, const std::string& path = "", Color* key = new Color (255, 0, 255));
        virtual ~Texture();
        virtual void free ();

        virtual bool load_from_file (const std::string& path, SDL_Renderer* renderer, Color* key = NULL);

    private:
        SDL_Texture*    _texture;
        unsigned int    _width;
        unsigned int    _height;

    /// Mutators
    public:
        inline void set_texture (SDL_Texture* texture)              { _texture = texture; }
        inline void set_size (const int& width, const int& height)  { _width = width; _height = height; }
        inline void set_color (Color* color)                        { SDL_SetTextureColorMod(_texture, color->r, color->g, color->b); }
        inline void set_color (Uint8 r, Uint8 g, Uint8 b)           { SDL_SetTextureColorMod(_texture, r, g, b); }
        inline void set_alpha (Color* color)                        { SDL_SetTextureAlphaMod(_texture, color->a); }
        inline void set_alpha (Uint8 alpha)                         { SDL_SetTextureAlphaMod(_texture, alpha); }
        inline void set_blend_mode (SDL_BlendMode blend)            { SDL_SetTextureBlendMode(_texture, blend); }

    /// Accessors
    public:
        inline SDL_Texture* texture()                               { return _texture; }
        inline const unsigned int& width() const                    { return _width; }
        inline const unsigned int& height() const                   { return _height; }
};

#endif // TEXTURE_HPP
