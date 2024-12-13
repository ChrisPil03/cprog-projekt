#include "Session.h"
#include "Sprite.h"
#include "Component.h"
#include "Animation.h"
#include <string>
#include "Collider2D.h"
#include "RigidBody.h"
#include "Map.h"
#include <iostream>

using namespace engine;
//spelklass
class Player : public Sprite{
public:
    Player(int x, int y, int w, int h):
        Sprite(x, y, w, h, Animation::getInstance("Idle", "/images/BlueSlimeIdle.png", 32, 32, 6, 10, true)),
        collider(Collider2D::getInstance(x,y,40,32,"Player")),
        rgdb(RigidBody::getInstance(this, collider, "Ground"))
    {
        collider->setParent(this);
        rgdb->setElasticity(3);
        addAnimation(Animation::getInstance("Jump", "/images/BlueSlimeJump.png", 32, 32, 3, 1, false));
        addAnimation(Animation::getInstance("Fall", "/images/BlueSlimeFall.png", 32, 32, 3, 1, false));
    }

    void update(){
        rgdb->targetVelocityX = 0;
        if (session.keyDown("A")){
            rgdb->targetVelocityX = -speed;
            if (!hasFlipped){
                hasFlipped = true;
                flipX();
            }
        }
        if (session.keyDown("D")){
            rgdb->targetVelocityX = speed;
            if (hasFlipped){
                hasFlipped = false;
                flipX();
            }
        }
        if(rgdb->isGrounded()){
            playAnimation("Idle");
            
            if (session.keyDown("W")){
                playAnimation("Jump");
                rgdb->velocityY = jumpForce;
            }
        }
        if (!rgdb->isGrounded() && rgdb->velocityY > 5){
            playAnimation("Fall");
        }

    }

    void onCollision(Component* other){
        if(other->getTag() == "Coin"){
            session.removeComponent(other->getParent());
            session.removeComponent(other);
        }
    }

    ~Player(){
        session.removeComponent(collider);
        session.removeComponent(rgdb);
    }
private: 
    Collider2D* collider;
    RigidBody* rgdb;

    int speed = 3;
    int jumpForce = -5;

    bool hasFlipped = false;
    bool isGrounded = true;
};

//spelklass
class Pickup : public Sprite{
    public:
        Pickup(int x, int y, int w, int h, std::string imagePath, std::string tag) :
            Sprite(x,y,w,h,imagePath), collider(Collider2D::getInstance(x,y,w,h,tag))
        {
            collider->setParent(this);
        }
        
        ~Pickup(){
            // std::cout<< "remove pickup collider"<< std::endl;
            // session.removeComponent(collider);
            // Why does it not work to remove collider here?
        }
    private:
        Collider2D* collider;
};

int main (int argc, char** argv){

    std::vector<std::vector<int>> tileMap = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
    };

    Pickup* coin = new Pickup(300,512,16,16,"/images/GoldCoin.png","Coin");
    Player* player = new Player(300,100,64,64);
    Map* map = Map::getInstance(tileMap, "/images/TileMap.png",16,65,2, "Ground");

    session.addComponent(map);
    session.addComponent(coin);
    session.addComponent(player);
    session.run();

    return 0;
}