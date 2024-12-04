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
    private:
        float gravity;
        float velocity;
        float mass;
        float friction;
        float elasticity;
        Collider2D* collider;
    };
}

#endif