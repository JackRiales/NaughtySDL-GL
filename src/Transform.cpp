#include "Transform.hpp"

Transform2D::Transform2D(const Vector2D<int>& position, const double& rotation, SDL_Point* center, SDL_RendererFlip flip):
_position (position),
_rotation (rotation),
_center (center),
_flip (flip)
{
    ;
}
