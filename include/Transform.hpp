#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <SDL.h>
#include "Vector.hpp"

class Transform2D
{
    public:
        Transform2D (const Vector2D<int>& position = 0,
                     const double& rotation = 0.0,
                     SDL_Point* center = NULL,
                     SDL_RendererFlip flip = SDL_FLIP_NONE);
        ~Transform2D ();

    private:
        Vector2D<int>    _position;
        double           _rotation;
        SDL_Point*       _center;
        SDL_RendererFlip _flip;

    /// Mutators
    public:
        inline void set_position (const Vector2D<int>& position) { _position = position; }
        inline void set_position (const int& x, const int& y) { _position.x = x; _position.y = y; }
        inline void set_rotation (const double& rotation) { _rotation = rotation; }
        inline void set_origin (SDL_Point* center) { _center = center; }
        inline void set_flip (SDL_RendererFlip flip) { _flip = flip; }

    /// Accessors
    public:
        inline const Vector2D<int>& position() { return _position; }
        inline const double& rotation() { return _rotation; }
};

#endif // TRANSFORM_HPP
