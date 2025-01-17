#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "AnimatedSprite.h"
#include "Component.h"
#include "Collider2D.h"
#include "RigidBody.h"
#include <string>

namespace game
{
    class Player : public engine::AnimatedSprite
    {
    public:
        static Player* getInstance(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey,
            std::string idleAnimPath, std::string jumpAnimPath, std::string fallAnimPath);
        void update();
        void handleInputs();
        void onCollision(Component* other);
        ~Player();
    
    private: 
        Player(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey,
            std::string IdleAnimPath, std::string JumpAnimPath, std::string FallAnimPath);
    
        engine::Collider2D* collider;
        engine::RigidBody* rgdb;

        int speed = 3;
        int groundSpeedX = 0;
        int jumpForce = -6;
        int relSpeed = speed;

        bool hasFlipped = false;
        bool isGrounded = true;
        bool onPlatform = false;

        std::string moveLeftKey;
        std::string moveRightKey;
        std::string jumpKey;
        std::string color;
    };
}

#endif