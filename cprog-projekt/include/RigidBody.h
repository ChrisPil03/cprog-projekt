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
        void update();
        bool isGrounded(){ return grounded; }
        void setIsOnPlatform(bool value){ isOnPlatform = value;}

        float velocityY = 0;
        float velocityX = 0;
        int targetVelocityX = 0;
    private:
        RigidBody(Component* parent, Collider2D* collider, std::string groundTag);

        void updateVelocity();
        void setParentPosition();
        void bounce();

        int gravity = 9;
        int mass;
        int friction;
        int elasticity = 0;
        bool grounded;
        bool isOnPlatform = false;
        Collider2D* collider;
        std::string groundTag;
    };
}

#endif