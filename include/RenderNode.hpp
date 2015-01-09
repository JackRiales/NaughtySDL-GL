#ifndef RENDER_NODE_HPP
#define RENDER_NODE_HPP

#include <SDL.h>

class IRenderNode
{
    public:
        IRenderNode (const unsigned int layer = 0) : _layer (layer) { ; }
        virtual ~IRenderNode () { ; }

        virtual void render(SDL_Renderer* renderer) = 0;

    protected:
        unsigned int _layer;

    /// Accessor(s)
    public:
        const unsigned int& layer () { return _layer; }
};

#endif // RENDER_NODE_HPP
