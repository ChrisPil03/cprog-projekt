#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Sprite.h"
#include "Component.h"
#include "Collider2D.h"
#include "RigidBody.h"
#include <string>

namespace game
{
    class Player : public engine::Sprite
    {
    public:
        Player(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey);
        ~Player();
        void update();
        void handleInputs();
        void onCollision(Component* other);

    private: 
        engine::Collider2D* collider;
        engine::RigidBody* rgdb;

        int speed = 3;
        int groundSpeed = 0;
        int jumpForce = -6;

        bool hasFlipped = false;
        bool isGrounded = true;
        bool onPlatform = false;

        std::string moveLeftKey;
        std::string moveRightKey;
        std::string jumpKey;
    };
}

#endif