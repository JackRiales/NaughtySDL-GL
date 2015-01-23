#include "Text.hpp"

Text::Text
(
SDL_Renderer* renderer,
const std::string& path_to_font,
const std::string& text,
const Transform2D& trans,
const unsigned int& font_size,
const Color& color
):
_texture    (NULL),
_font       (NULL),
_text       (text),
_transform  (trans),
_size       (font_size),
_color      (color)
{
    if (!load_from_file (path_to_font, renderer))
    {
        printf ("Text failed to load! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

Text::~Text()
{
    // Deallocate
    free();
}

void Text::render (SDL_Renderer* renderer)
{
    SDL_Rect render_quad =
    {
        _transform.position().x,
        _transform.position().y,
        (int)_texture->width(),
        (int)_texture->height()
    };

    SDL_RenderCopyEx
    (
        renderer,
        texture()->texture(),
        NULL,
        &render_quad,
        _transform.rotation(),
        _transform.origin(),
        _transform.flip()
    );
}

void Text::free()
{
    if (texture() != NULL)
    {
        texture()->free();
    }

    if (_font != NULL)
    {
        TTF_CloseFont(_font);
        _font = NULL;
    }
}

bool Text::load_from_file(const std::string& path, SDL_Renderer* renderer)
{
    // Deallocate
    free();

    // Form font from path
    _font = TTF_OpenFont(path.c_str(), _size);
    if (_font == NULL)
    {
        printf( "Failed to load font at %s. SDL_ttf Error: %s\n", path.c_str(), TTF_GetError() );
        return false;
    }

    // Generate texture
    SDL_Color __col = { _color.r, _color.g, _color.b, _color.a };
    SDL_Texture* new_texture = NULL;
    SDL_Surface* text_surface = TTF_RenderText_Solid(_font, _text.c_str(), __col);
    if (text_surface == NULL)
    {
        printf ("Unable to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    else
    {
        new_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if( new_texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            _texture = new Texture (new_texture);
            _texture->set_size (text_surface->w, text_surface->h);
        }
        SDL_FreeSurface(text_surface);
    }

    return texture() != NULL;
}
