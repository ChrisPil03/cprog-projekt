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
        void addForce(float xForce, float yForce);
        void setGravity(float gravity);
        void update();

        float velocityY = 2.0f;
        float velocityX = 0;
    private:
        void updateVelocity();

        float gravity = 2.0f;
        float mass;
        float friction;
        float elasticity;
        Collider2D* collider;
        std::string groundTag;
    };
}

#endif