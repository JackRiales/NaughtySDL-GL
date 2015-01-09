#include "TextureManager.hpp"

template <typename T>
TextureManager<T>::TextureManager(SDL_Renderer* renderer) :
_renderer (renderer)
{
    ;
}

template <typename T>
TextureManager<T>::~TextureManager()
{
    for (typename std::map<T, SDL_Texture*>::iterator itr = _bin.begin(); itr != _bin.end(); ++itr)
    {
        SDL_DestroyTexture(itr->second);
        itr->second = NULL;
    }
}

template <typename T>
bool TextureManager<T>::load(const T& key, const std::string& path)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load (path.c_str());
    if (surface == NULL)
    {
        printf ("Unable to load image at %s. SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( _renderer, surface );
        if (texture == NULL)
        {
            printf ("Failed to create texture from surface. SDL_Error: %s\n", SDL_GetError());
            return false;
        }

        SDL_FreeSurface( surface );

        _bin.insert( std::pair<T, SDL_Texture*>(key, texture) );
    }

    return true;
}
