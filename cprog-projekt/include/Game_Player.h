#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Sprite.h"
#include "Component.h"
#include "Collider2D.h"
#include "RigidBody.h"

namespace game
{
    class Player : public engine::Sprite
    {
    public:
        Player(int x, int y, int w, int h);
        ~Player();
        void update();
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
    };
}

#endif