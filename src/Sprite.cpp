#include "Sprite.hpp"

Sprite::Sprite(Texture* sheet):
_sheet (sheet),
_position (*new Vector2D<int>)
{
    _area = { 0, 0, (int) _sheet->width(), (int) _sheet->height() };
}

Sprite::Sprite(Texture* sheet, Vector2D<int>* position):
_sheet (sheet),
_position (*position)
{
    _area = { 0, 0, (int) _sheet->width(), (int) _sheet->height() };
}

Sprite::Sprite(Texture* sheet, const SDL_Rect& area, Vector2D<int>* position):
_sheet (sheet),
_area (area),
_position (*position)
{
    ;
}

Sprite::Sprite(Texture* sheet, const SDL_Rect& area, const int& x, const int& y):
_sheet (sheet),
_area (area),
_position (x, y)
{
    ;
}

Sprite::Sprite (Texture* sheet, int uv_x, int uv_y, int uv_w, int uv_h, Vector2D<int>* position):
_sheet (sheet),
_position (*position)
{
    if (uv_w < 0)
    {
        uv_w = _sheet->width();
    }

    if (uv_h < 0)
    {
        uv_h = _sheet->height();
    }

    _area = { uv_x, uv_y, uv_w, uv_h };
}

Sprite::Sprite(Texture* sheet, int uv_x, int uv_y, int uv_w, int uv_h, int x, int y):
_sheet (sheet),
_position (x, y)
{
    if (uv_w < 0)
    {
        uv_w = _sheet->width();
    }

    if (uv_h < 0)
    {
        uv_h = _sheet->height();
    }

    _area = { uv_x, uv_y, uv_w, uv_h };
}

Sprite::~Sprite()
{
    ;
}

void Sprite::render(SDL_Renderer* renderer)
{
    SDL_Rect render_quad = {position().x,
                            position().y,
                            (int)_sheet->width(),
                            (int)_sheet->height()};

    _sheet->set_size( _area.w, _area.h );

    SDL_RenderCopy(renderer, _sheet->texture(), &_area, &render_quad);
}
