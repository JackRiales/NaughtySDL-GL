#include "SurfaceManager.hpp"

template <typename T>
SurfaceManager<T>::SurfaceManager(SDL_Surface* screen) :
_main_window (screen)
{

}

template <typename T>
SurfaceManager<T>::~SurfaceManager()
{
    for (typename std::map<T, SDL_Surface*>::iterator itr = _bin.begin(); itr != _bin.end(); ++itr)
    {
        SDL_FreeSurface(itr->second);
        itr->second = NULL;
    }
}

template <typename T>
bool SurfaceManager<T>::load_image (const T& key, const std::string& path)
{
    SDL_Surface** surface = &_bin[key];
    surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        printf ( "Unable to load image at %s; SDL Error: %s\n", path.c_str(), IMG_GetError() );
        return false;
    }
    if (optimize (surface, _main_window))
    {
        printf ("Image %s optimized to screen.", path.c_str());
    }
    return true;
}

template <typename T>
bool SurfaceManager<T>::optimize (SDL_Surface* surface_to_optimize, const SDL_Surface* screen_surface_ref)
{
    SDL_Surface* temp_optimized = SDL_ConvertSurface(surface_to_optimize, screen_surface_ref->format, NULL);
    if (temp_optimized == NULL)
    {
        printf ("Unable to optimize image. SDL Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        SDL_FreeSurface(surface_to_optimize);
        surface_to_optimize = temp_optimized;
    }
    return true;
}

template <typename T>
bool SurfaceManager<T>::convert_texture (SDL_Texture* null_texture, SDL_Renderer* renderer, const T& key)
{
    null_texture = SDL_CreateTextureFromSurface(renderer, get(key));
    if (null_texture == NULL)
    {
        printf ("Failed to create texture from surface. SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}
