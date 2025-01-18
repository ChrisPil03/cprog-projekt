#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "AnimatedSprite.h"
#include "Collider2D.h"
#include "RigidBody.h"

#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64

#define BLUE_IDLE_ANIM "/images/BlueSlimeIdle.png"
#define BLUE_JUMP_ANIM "/images/BlueSlimeJump.png"
#define BLUE_FALL_ANIM "/images/BlueSlimeFall.png"
#define RED_IDLE_ANIM "/images/RedSlimeIdle.png"
#define RED_JUMP_ANIM "/images/RedSlimeJump.png"
#define RED_FALL_ANIM "/images/RedSlimeFall.png"

namespace game
{
    class Player : public engine::AnimatedSprite
    {
    public:
        static Player* getInstance(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey,
            std::string color);
        void update();
        void handleInputs();
        void onCollision(Component* other);
        const std::string& getColor(){ return color; }
        void respawn();
        ~Player();
    
    private: 
        Player(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey,
            std::string color);
    
        engine::Collider2D* collider;
        engine::RigidBody* rgdb;

        int spawnPointX;
        int spawnPointY;
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