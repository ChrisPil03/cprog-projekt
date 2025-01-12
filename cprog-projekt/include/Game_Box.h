#ifndef BOX_H
#define BOX_H

#include "Sprite.h"
#include "Collider2D.h"
#include "RigidBody.h"

#define IMAGE_PATH {"/images/Box.png"}

namespace game{
    class Box : public engine::Sprite
    {
    public:
        static Box* getInstance(int x, int y, int w, int h);
        ~Box();
    private:
        Box(int x, int y, int w, int h);
        engine::Collider2D* collider;
        engine::RigidBody* rgdb;
    };
}

#endif