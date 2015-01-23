#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Texture.hpp"
#include "RenderNode.hpp"
#include "Transform.hpp"

class Text : public IRenderNode
{
    public:
        Text (SDL_Renderer* renderer,
              const std::string& path_to_font,
              const std::string& text = "",
              const Transform2D& trans = *new Transform2D (0, 0),
              const unsigned int& font_size = 12,
              const Color& color = *new Color);

        virtual ~Text();
        virtual void free();

        virtual void render(SDL_Renderer* renderer);

    private:
        Texture*        _texture;
        TTF_Font*       _font;
        std::string     _text;
        Transform2D     _transform;
        unsigned int    _size;
        Color           _color;

    /// Mutators
    public:
        void set_font_size (const unsigned int& font_size);
        void set_text (const unsigned int& text);

    /// Accessors
    public:
        inline Texture* texture()           { return _texture; }
        inline const std::string& text()    { return _text; }

    /// Protected methods
    protected:
        virtual bool load_from_file (const std::string& path, SDL_Renderer* renderer);
};

#endif // TEXT_HPP
