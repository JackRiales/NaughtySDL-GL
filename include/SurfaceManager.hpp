#ifndef SURFACE_MANAGER_HPP
#define SURFACE_MANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <map>

template <typename T>
class SurfaceManager
{
    public:
        SurfaceManager (SDL_Surface* screen = NULL);
        ~SurfaceManager ();

        bool load_image (const T& key, const std::string& path);
        bool optimize (SDL_Surface* surface_to_optimize, const SDL_Surface* screen_surface_ref);

        bool convert_texture (SDL_Texture* null_texture, SDL_Renderer* renderer, const T& key);

    private:
        SDL_Surface* _main_window;
        std::map <T, SDL_Surface*> _bin;

    /// Accessors
    public:
        inline const SDL_Surface* get(const T& key) const { return _bin[key]; }
        inline const std::map<T, SDL_Surface*>& bin() const { return _bin; }
};

#include "../src/SurfaceManager.inl"

typedef SurfaceManager<std::string> STR_SurfaceManager;
typedef SurfaceManager<int>         INT_SurfaceManager;
typedef SurfaceManager<char>        CHAR_SurfaceManager;

#endif // SURFACE_MANAGER_HPP
