#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "Component.h"
#include "Collider2D.h"
#include "Sprite.h"
#include "Game_Player.h"
#include "Game_Platform.h"

namespace game {
    class Button : public engine::Sprite {
    public:
        static Button* getInstance(int x, int y, int w, int h, std::string imagePath, Platform* platform);
        void update();
        ~Button();
    private:
        Button(int x, int y, int w, int h, std::string imagePath, Platform* platform);
        engine::Collider2D* collider;

        Platform* platform;
        
    };
}

#endif

