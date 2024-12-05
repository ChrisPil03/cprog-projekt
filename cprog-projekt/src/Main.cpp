#include "Session.h"
#include "Sprite.h"
#include "Component.h"
#include "Animation.h"
#include <string>
#include "Collider2D.h"
#include "RigidBody.h"
#include <iostream>

using namespace engine;

class Player : public Sprite{
public:
    Player(int x, int y, int w, int h):
        Sprite(x, y, w, h, Animation::getInstance("/images/BlueSlimeIdle.png", 32, 32, 6, 10)),
        collider(new Collider2D(x,y,75,55,"Player")),
        rgdb(new RigidBody(this, collider, "Ground"))
    {
        collider->setParent(this);
    }

    void update(){
        rgdb->targetVelocityX = 0;
        if (session.keyDown(SDLK_a)){
            rgdb->targetVelocityX = -2;
            if (!hasFlipped){
                hasFlipped = true;
                flipX();
            }
        }
        if (session.keyDown(SDLK_d)){
            rgdb->targetVelocityX = 2;
            if (hasFlipped){
                hasFlipped = false;
                flipX();
            }
        }
        if (session.keyDown(SDLK_w) && rgdb->isGrounded()){
            rgdb->targetVelocityY = -8;
        }
    }

    ~Player()
    {
        delete collider;
        delete rgdb; 
    }
private: 
    Collider2D* collider;
    RigidBody* rgdb;
    
    bool hasFlipped = false;
    bool isGrounded = true;
};

class Ground : public Sprite{
    public:
        Ground(int x, int y, int w, int h, std::string txt) 
            : Sprite(x,y,w,h,txt), collider(new Collider2D(x,y,w,h,"Ground")){
                collider->setParent(this);
            }

        ~Ground(){ delete collider; }
    private:
        Collider2D* collider;
};


int main (int argc, char** argv){

    Player* player = new Player(300,100,128,128);
    Ground* obstacle = new Ground(500,350,50,50,"/images/bg.jpg");
    Ground* ground = new Ground(150,400,660,50, "/images/bg.jpg");
    session.addComponent(obstacle);
    session.addComponent(ground);
    session.addComponent(player);
    session.run();

    return 0;
}