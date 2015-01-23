#include "Texture.hpp"

Texture::Texture():
_texture (NULL)
{
    ;
}

Texture::Texture(SDL_Texture* texture):
_texture (texture)
{
    ;
}

Texture::Texture (SDL_Renderer* renderer, const std::string& path, Color* key):
_texture (NULL)
{
    if (path != "")
    {
        printf ("Creating new texture from %s...\n", path.c_str());
        load_from_file (path, renderer, key);
    }
}

Texture::~Texture()
{
    free();
}

bool Texture::load_from_file(const std::string& path, SDL_Renderer* renderer, Color* key)
{
    free ();
    SDL_Texture* new_texture = NULL;
    SDL_Surface* loaded_surface = IMG_Load ( path.c_str() );

    if (loaded_surface == NULL)
    {
        printf ( "Unable to load image at %s. SDL_Image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        if (key != NULL)
        {
            SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB (loaded_surface->format, key->r, key->g, key->b) );
        }

        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (new_texture == NULL)
        {
            printf (" Unable to create texture from %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            _width = loaded_surface->w;
            _height = loaded_surface->h;
        }

        SDL_FreeSurface(loaded_surface);
    }

    _texture = new_texture;
    return _texture != NULL;
}

void Texture::free()
{
    if (_texture != NULL)
    {
        SDL_DestroyTexture (_texture);
        _texture = NULL;
        _width = 0;
        _height = 0;
    }
}
