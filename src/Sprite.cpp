#include "Sprite.hpp"

Sprite::Sprite(Texture* sheet, SDL_Rect* area, Transform2D* trans):
_sheet (sheet),
_transform (*trans)
{
    if (area != NULL)
    {
        _area = *area;
    }
    else
    {
        _area = { 0, 0, (int) _sheet->width(), (int) _sheet->height() };
    }
}

Sprite::~Sprite()
{
    ;
}

void Sprite::render(SDL_Renderer* renderer)
{
    SDL_Rect render_quad =
    {
        position().x,
        position().y,
        (int)_sheet->width(),
        (int)_sheet->height()
    };

    _sheet->set_size
    (
        _area.w,
        _area.h
    );

    SDL_RenderCopyEx
    (
        renderer,
        _sheet->texture(),
        &_area,
        &render_quad,
        _transform.rotation(),
        _transform.origin(),
        _transform.flip()
    );
}
