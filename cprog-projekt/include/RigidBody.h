#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Component.h"
#include "Collider2D.h"

namespace engine{
    class RigidBody : public Component
    {
    public:
        RigidBody(Component* parent, Collider2D* collider);
        void addForce(float xForce, float yForce);
        void setGravity(float gravity);
        void update();

        float velocityY = 0;
        float velocityX = 0;
    private:
        void updateVelocity();

        float gravity;
        float mass;
        float friction;
        float elasticity;
        Collider2D* collider;
    };
}

#endif