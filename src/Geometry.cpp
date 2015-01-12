#include "Geometry.hpp"

Geometry2D::Geometry2D (const int& x, const int& y, const int& w, const int& h, unsigned int layer, int type):
IRenderNode (layer),
_draw_color (new Color (255, 255, 255, 255)),
_type ( (Geo_Type) type ),
_dotted_increment (4)
{
    _rect = { x, y, w, h };
}

Geometry2D::~Geometry2D()
{

}

void Geometry2D::render (SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(
                            renderer,
                            _draw_color->r,
                            _draw_color->g,
                            _draw_color->b,
                            _draw_color->a
                          );

    switch (_type)
    {
    case (FILLED):
        SDL_RenderFillRect(renderer, &_rect);
        break;

    case (OUTLINE):
        SDL_RenderDrawRect(renderer, &_rect);
        break;

    case (LINEAR):
        SDL_RenderDrawLine (renderer, _rect.x, _rect.y, _rect.w, _rect.h);
        break;

    case (DOTTED):
        draw_dotted (renderer, _dotted_increment);
        break;

    case (LINEAR_DOTTED):
        draw_dotted_line (renderer, _dotted_increment);
        break;

    default:
        printf ("Geometry type not in range. Render method failed.");
        break;
    }
}

void Geometry2D::draw_dotted (SDL_Renderer* renderer, const unsigned int& spacing)
{
    for (int x = _rect.x; x < _rect.w; x += spacing)
    {
        for (int y = _rect.y; y < _rect.h; y += spacing)
        {
            SDL_RenderDrawPoint (renderer, x, y);
        }
    }
}

void Geometry2D::draw_dotted_line(SDL_Renderer* renderer, const unsigned int& spacing)
{

}
