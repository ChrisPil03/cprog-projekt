#include "Game_Box.h"
#include "Session.h"

namespace game
{
    Box* Box::getInstance(int x, int y, int w, int h){
        return new Box(x,y,w,h);
    }

    Box::Box(int x, int y, int w, int h) : Sprite(x,y,w,h,IMAGE_PATH),
        collider(engine::Collider2D::getInstance(x,y,w,h,"Box")),
        rgdb(engine::RigidBody::getInstance(this, collider, "Ground"))
    {
        collider->setParent(this);
    }

    Box::~Box(){
        engine::session.removeComponent(collider);
        engine::session.removeComponent(rgdb);
    }
}