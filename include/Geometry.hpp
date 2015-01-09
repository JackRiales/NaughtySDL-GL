#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <stdio.h>

#include "RenderNode.hpp"
#include "Color.hpp"

class Geometry : public IRenderNode
{
    public:
        /// Constructor
        Geometry
        (
         const int& x = 0.f,
         const int& y = 0.f,
         const int& w = 0.f,
         const int& h = 0.f,
         unsigned int layer = 0,
         int type = FILLED
        );

        /// Destructor
        virtual ~Geometry ();

        /// Calls a renderer to draw geometry
        void render (SDL_Renderer* renderer) override;

        /// Determines whether the figure is drawn filled or with just an outline
        enum Geo_Type
        {
            FILLED          = 0,
            OUTLINE         = 1,
            LINEAR          = 2,
            DOTTED          = 3,
            LINEAR_DOTTED   = 4,
        };
    private:
        SDL_Rect    _rect;
        Color*      _draw_color;
        Geo_Type    _type;
        unsigned int _dotted_increment;

    /// Mutators
    public:
        inline void set_color (Color* color) { _draw_color = color; }
        inline void set_color (const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a = 0xFF) { _draw_color = new Color (r, g, b, a); }
        inline void set_dotted_increment (const unsigned int& increment) { _dotted_increment = increment; }

    /// Accessors
    public:
        inline const SDL_Rect& rect () { return _rect; }
        inline const Color* color () { return _draw_color; }
        inline const int type () { return _type; }

    /// Private methods
    private:
        void draw_dotted (SDL_Renderer* renderer, const unsigned int& spacing);
        void draw_dotted_line (SDL_Renderer* renderer, const unsigned int& spacing);
};

#endif // GEOMETRY_HPP
