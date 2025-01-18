#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include "Component.h"
#include "Collider2D.h"
#include "Sprite.h"
#include "Game_Player.h"
#include "Game_Platform.h"

#define BUTTON_NORMAL "/images/GameButton_Normal.png"
#define BUTTON_PRESSED "/images/GameButton_Pressed.png"

namespace game {
    class Button : public engine::Sprite {
    public:
        static Button* getInstance(int x, int y, int w, int h, Platform* platform);
        void update();
        ~Button();
    private:
        Button(int x, int y, int w, int h, Platform* platform);
        engine::Collider2D* collider;
        bool buttonPressed;

        Platform* platform;
    };
}

#endif

