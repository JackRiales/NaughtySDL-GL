#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "RenderNode.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "Transform.hpp"

class Sprite : public IRenderNode
{
    public:
        Sprite (Texture* sheet);
        Sprite (Texture* sheet, Vector2D<int>* position);
        Sprite (Texture* sheet, const SDL_Rect& area, Vector2D<int>* position = new Vector2D<int>);
        Sprite (Texture* sheet, const SDL_Rect& area, const int& x = 0, const int& y = 0);
        Sprite (Texture* sheet, int uv_x, int uv_y, int uv_w = -1, int uv_h = -1, Vector2D<int>* position = new Vector2D<int>);
        Sprite (Texture* sheet, int uv_x, int uv_y, int uv_w = -1, int uv_h = -1, int x = 0, int y = 0);
        virtual ~Sprite();

        virtual void render (SDL_Renderer* renderer) override;

    private:
        Texture*            _sheet;
        SDL_Rect            _area;
        Transform2D         _transform;

    /// Mutators
    public:
        inline void apply_texture (Texture* sheet) { _sheet = sheet; }
        inline void set_area (const SDL_Rect& area){ _area = area; }
        inline void set_area (const int& x, const int& y, const unsigned int& w, const unsigned int& h) { _area = { x, y, (int) w, (int) h }; }
        inline void set_position (Vector2D<int>* position) { _transform.set_position(*position); }
        inline void set_position (const int& x, const int& y) { _transform.set_position(x, y); }

    /// Accessors
    public:
        inline Texture* texture () { return _sheet; }
        inline const SDL_Rect& area () { return _area; }
        inline const Vector2D<int>& position(){ return _transform.position(); }
};

#endif // SPRITE_HPP
