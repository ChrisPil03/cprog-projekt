#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Component.h"
#include "Collider2D.h"
#include <string>

namespace engine{
    class RigidBody : public Component
    {
    public:
        static RigidBody* getInstance(Component* parent, Collider2D* collider, std::string groundTag);
        
        void setGravity(int gravity) { this->gravity = gravity; }
        void setElasticity(int elasticity) { this->elasticity = elasticity; }
        void setAccelerateX(bool accelerate) { accelerateX = accelerate; }
        void setVelocityY(float velocity) { velocityY = velocity; }
        void setVelocityX(float velocity) { velocityX = velocity; }
        void setTargetVelocityX(int velocity) { targetVelocityX = velocity; }
        const int getTargetVelocityX() { return targetVelocityX; }
        const float getVelocityY() { return velocityY; }
        const float getVelocityX() { return velocityX; }
        void update();
        const bool isGrounded(){ return grounded; }
        void setIsOnPlatform(bool value){ isOnPlatform = value;}

    private:
        RigidBody(Component* parent, Collider2D* collider, std::string groundTag);

        void updateVelocity();
        void setParentPosition();
        void bounce();
        void horizontalCollision(Collider2D* other, int lastXPos);
        void verticalCollision(Collider2D* other, int lastYPos, int lastXPos);

        float velocityY;
        float velocityX;
        int targetVelocityX;
        int gravity = 9;
        int mass;
        int friction;
        int elasticity = 0;
        float accelerationX;
        bool accelerateX;
        bool grounded;
        bool isOnPlatform = false;
        Collider2D* collider;
        std::string groundTag;
    };
}

#endif