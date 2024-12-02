#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"

namespace engine{
    class Collider2D : public Component{
        public:
            Collider2D(int x, int y, int w, int h, Sprite* sprite, std::string tag);
            bool hasCollided(std::string tagName);
            const std::string& getTag() const {return tag; }
            const SDL_Rect* getColliderRect() const { return &collider; }            
            void update();
            void updateCollider(); //ny

        private:
            SDL_Rect collider;
            std::string tag;
            Sprite* belongsTo;
    };
}

#endif