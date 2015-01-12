#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <ctime>
#include <vector>

#include "Sprite.hpp"

class AnimatedSprite : public Sprite
{
    public:
        AnimatedSprite(Texture* sheet, const std::vector<SDL_Rect>& frames);
        AnimatedSprite(Texture* sheet, SDL_Rect frames[], const unsigned int& frame_count);
        virtual ~AnimatedSprite();

        virtual void render (SDL_Renderer* renderer);

    private:
        std::vector <SDL_Rect>  _frames;
        unsigned int            _frame_time;

    /// Mutators
    public:
        inline void set_frames ( const std::vector<SDL_Rect>& frames ) { _frames = frames; }
        inline void add_frame (const SDL_Rect& new_frame) { _frames.push_back(new_frame); }
        inline void set_timing (const unsigned int& t) { _frame_time = t; }

    /// Accessors
    public:
        inline const std::vector<SDL_Rect>& frames() { return _frames; }
        inline const SDL_Rect& frame (const int& index) { return _frames[index]; }
        inline const SDL_Rect& operator[](const int& index) { return _frames[index]; }
        inline const unsigned int& frame_time () { return _frame_time; }
};

#endif // ANIMATED_SPRITE_HPP
