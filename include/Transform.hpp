#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <SDL2/SDL.h>
#include "Vector.hpp"

class Transform2D
{
    public:
        Transform2D (const iVector2D& position = 0,
                     const double& rotation = 0.0,
                     SDL_Point* center = NULL,
                     SDL_RendererFlip flip = SDL_FLIP_NONE);
        Transform2D (const int& x = 0, const int& y = 0,
                     const double& rotation = 0.0,
                     SDL_Point* center = NULL,
                     SDL_RendererFlip flip = SDL_FLIP_NONE);
        ~Transform2D ();

    private:
        iVector2D           _position;
        double              _rotation;
        SDL_Point*          _center;
        SDL_RendererFlip    _flip;

    /// Mutators
    public:
        inline void set_position (const iVector2D& position)    { _position = position; }
        inline void set_position (const int& x, const int& y)   { _position.x = x; _position.y = y; }
        inline void set_rotation (const double& rotation)       { _rotation = rotation; }
        inline void set_origin (SDL_Point* center)              { _center = center; }
        inline void set_flip (SDL_RendererFlip flip)            { _flip = flip; }

    /// Accessors
    public:
        inline const iVector2D& position() const    { return _position; }
        inline const double& rotation() const       { return _rotation; }
        inline SDL_Point* origin() const            { return _center; }
        inline const SDL_RendererFlip& flip() const { return _flip; }
};

#endif // TRANSFORM_HPP
