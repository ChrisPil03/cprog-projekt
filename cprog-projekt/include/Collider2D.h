#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

namespace engine{
    class Collider2D : public Component
    {
    public:
        Collider2D(int x, int y, int w, int h, std::string tag);
        bool hasCollided(std::string tagName);
        void collisionXAxis(std::string tagName);
        void collisionYAxis(std::string tagName);
        const std::string getTag() const { return tag; }
        const SDL_Rect* getColliderRect() const { return &collider; }
        void updateCollider();
    private:
        SDL_Rect collider;
        std::string tag;
    };
}

#endif