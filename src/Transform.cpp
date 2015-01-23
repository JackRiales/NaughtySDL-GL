#include "Transform.hpp"

Transform2D::Transform2D(const iVector2D& position, const double& rotation, SDL_Point* center, SDL_RendererFlip flip):
_position (position),
_rotation (rotation),
_center (center),
_flip (flip)
{
    ;
}

Transform2D::Transform2D(const int& x, const int& y, const double& rotation, SDL_Point* center, SDL_RendererFlip flip):
Transform2D(
*new iVector2D (x, y),
rotation,
center,
flip)
{

}

Transform2D::~Transform2D()
{
    ;
}
