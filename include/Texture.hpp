#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <stdio.h>

#include "RenderNode.hpp"
#include "Vector.hpp"
#include "Color.hpp"

class Texture : public IRenderNode
{
    public:
        Texture (SDL_Renderer* renderer,
                 const std::string& path = "",
                 Color* key = new Color (255, 0, 255),
                 const int& x = 0,
                 const int& y = 0,
                 const unsigned int& layer = 0);

        virtual ~Texture();

        bool load_from_file (const std::string& path, SDL_Renderer* renderer, Color* key = NULL);

        void render (SDL_Renderer* renderer);

        void free ();

    private:
        SDL_Texture*    _texture;
        Vector2D<int>*  _position;
        unsigned int    _width;
        unsigned int    _height;

    /// Mutators
    public:
        void set_position (const int& x, const int& y);
        void set_size (const int& width, const int& height);

    /// Accessors
    public:
        inline const Vector2D<int>* position() const  { return _position; }
        inline const unsigned int& width() const { return _width; }
        inline const unsigned int& height() const{ return _height; }
};

#endif // TEXTURE_HPP
