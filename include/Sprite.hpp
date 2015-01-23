#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "RenderNode.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

class Sprite : public IRenderNode
{
    public:
        Sprite (Texture* sheet, SDL_Rect* area = NULL, Transform2D* trans = new Transform2D(0, 0));
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
        inline void set_position (iVector2D* position) { _transform.set_position(*position); }
        inline void set_position (const int& x, const int& y) { _transform.set_position(x, y); }
        inline void set_rotation (const double& rotation) { _transform.set_rotation(rotation); }

    /// Accessors
    public:
        inline Texture* texture ()              { return _sheet; }
        inline const SDL_Rect& area () const    { return _area; }
        inline const iVector2D& position() const{ return _transform.position(); }
        inline const double& rotation() const   { return _transform.rotation(); }
        inline SDL_Point* origin() const        { return _transform.origin(); }
};

#endif // SPRITE_HPP
