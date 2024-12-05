#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Component.h"
#include "Collider2D.h"
#include <string>

namespace engine{
    class RigidBody : public Component
    {
    public:
        RigidBody(Component* parent, Collider2D* collider, std::string groundTag);
        void addForce(int xForce, int yForce);
        void setGravity(int gravity);
        void update();
        bool isGrounded(){ return grounded; }

        int targetVelocityY = 2;
        int targetVelocityX = 0;
    private:
        void updateVelocity();
        void setParentPosition();

        double velocityY = 0;
        double velocityX = 0;
        int gravity = 5;
        int mass;
        int friction;
        int elasticity;
        bool grounded;
        Collider2D* collider;
        std::string groundTag;
    };
}

#endif