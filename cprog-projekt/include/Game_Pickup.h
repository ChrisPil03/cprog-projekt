#ifndef GAME_PICKUP_H
#define GAME_PICKUP_H

#include "Sprite.h"
#include "Collider2D.h"

namespace game
{
    class Pickup : public engine::Sprite
    {
    public:
        static Pickup* getInstance(int x, int y, int w, int h, std::string imagePath, std::string tag);
        ~Pickup();

    private:
        Pickup(int x, int y, int w, int h, std::string imagePath, std::string tag);

        engine::Collider2D* collider;
    };
}

#endif