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
class Platform : public Sprite{
    public:
        Platform(int x, int y, int w, int h, std::string imagePath, std::string tag) : 
            Sprite(x,y,w,h,imagePath), collider(Collider2D::getInstance(x,y,w,h,tag)),
                target1(Collider2D::getInstance(x+60+w,y,1, 10, "Target")),
                target2(Collider2D::getInstance(x-60,y,1, 10, "Target"))
        {
            collider->setParent(this);
        }

        void update(){        
           getRect()->x += speed;

           if(collider->hasCollided("Target")){
                speed *= -1;
           }
        }

        int getSpeed(){ return speed; }

        ~Platform(){
            session.removeComponent(collider);
            session.removeComponent(target1);
            session.removeComponent(target2);
        }

    private:
        Collider2D* collider;
        Collider2D* target1;
        Collider2D* target2;
        int speed = 2;
};

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
        rgdb->targetVelocityX = groundSpeed;
        if (session.keyDown("A")){
            rgdb->targetVelocityX = -speed + groundSpeed;
            if (!hasFlipped){
                hasFlipped = true;
                flipX();
            }
        }
        if (session.keyDown("D")){
            rgdb->targetVelocityX = speed + groundSpeed;
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
        if (Platform* platform = static_cast<Platform*>(other->getParent())){
            groundSpeed = platform->getSpeed();
            rgdb->targetVelocityX += groundSpeed;
            rgdb-> setIsOnPlatform(true);
        }else{
            groundSpeed = 0;
            rgdb-> setIsOnPlatform(false);
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
    int groundSpeed = 0;
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
        {1,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1},
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
    Platform* platform = new Platform(250, 500, 64, 64, "/images/bg.jpg", "Ground");
    Map* map = Map::getInstance(tileMap, "/images/TileMap.png",16,65,2, "Ground");

    session.addComponent(map);
    session.addComponent(coin);
    session.addComponent(player);
    session.addComponent(platform);
    session.run();

    return 0;
}