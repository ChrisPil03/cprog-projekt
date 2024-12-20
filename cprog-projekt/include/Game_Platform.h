#ifndef GAME_PLATFORM_H
#define GAME_PLATFORM_H

#include "Sprite.h"
#include "Collider2D.h"
#include "Session.h"

namespace game
{
    class Platform : public engine::Sprite
    {
    public:
        Platform(int x, int y, int w, int h, std::string imagePath, std::string tag);
        ~Platform();
        void update();
        const int getSpeed(){ return speed; }

    private:
        engine::Collider2D* collider;
        engine::Collider2D* target1;
        engine::Collider2D* target2;
        int speed = 1;
    };
}

#endif