#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <map>

template <typename T>
class TextureManager
{
    public:
        TextureManager (SDL_Renderer* renderer);
        ~TextureManager();

        bool load (const T& key, const std::string& path);

    private:
        SDL_Renderer* _renderer;
        std::map <T, SDL_Texture*> _bin;

    /// Accessors
    public:
        inline std::map<T, SDL_Texture*>& bin() { return _bin; }
};

#include "../src/TextureManager.inl"

typedef TextureManager<std::string> STR_TextureManager;
typedef TextureManager<int>         INT_TextureManager;
typedef TextureManager<char>        CHAR_TextureManager;

#endif // TEXTURE_MANAGER_HPP
