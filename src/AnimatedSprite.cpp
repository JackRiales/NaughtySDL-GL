#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(Texture* sheet, const std::vector<SDL_Rect>& frames):
Sprite (sheet),
_frames (frames)
{
    ;
}

AnimatedSprite::AnimatedSprite(Texture* sheet, SDL_Rect frames[], const unsigned int& frame_count):
Sprite (sheet),
_frames (frame_count)
{
    for (unsigned int i = 0; i < frame_count; ++i)
    {
        _frames[i] = frames[i];
    }
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::render(SDL_Renderer* renderer)
{
    Sprite::render(renderer);

    /// When time is implemented, use it to change frames
}
