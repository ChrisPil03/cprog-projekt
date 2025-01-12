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
        static Platform* getInstance(int x, int y, int w, int h, std::string imagePath, std::string tag, bool horizontal, int colPos1, int colPos2);
        ~Platform();
        void update();
        const int getSpeedX(){ return speedX; }
        const int getSpeedY(){ return speedY; }
        void setSpeedX(int speed){ speedX = speed; }
        void setSpeedY(int speed){ speedY = speed; }
        void setSpeed(int speedX, int speedY);
        void setIsControlled(bool controlled){ isControlled = controlled; }

    private:
        Platform(int x, int y, int w, int h, std::string imagePath, std::string tag, bool horizontal, int colPos1, int colPos2);
        engine::Collider2D* collider;
        engine::Collider2D* target1;
        engine::Collider2D* target2;
        int speedX = 0;
        int speedY = 0;
        bool horizontalMovement;
        bool isControlled;
    };
}

#endif