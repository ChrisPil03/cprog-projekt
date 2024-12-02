#include "Session.h"
#include "Sprite.h"
#include "Component.h"
#include <string>
#include <Collider2D.h>
//#include <SDL2/SDL.h>

using namespace engine;

class Player : public Sprite{
public:
    Player(int x, int y, int w, int h, std::string txt, int frames, int xFrame) 
        : Sprite(x, y, w, h, txt, frames, xFrame), collider(new Collider2D(x,y,128,128,this,"Player")){}
 
    void update(){


// nya collisionstestet
        if (session.keyDown(SDLK_w)){
            getRect()->y--;
            collider-> updateCollider (getRect()->y, getRect()->x);
            if(collider-> hasCollided("Ground")){
                getRect()->y++;
            }
        }

        if (session.keyDown(SDLK_a)){
            getRect()->x--;
            collider-> updateCollider (getRect()->y, getRect()->x);
            if(collider-> hasCollided("Ground")){
                getRect()->x++;
            }
        }

           if (session.keyDown(SDLK_s)){
            getRect()->y++;
            collider-> updateCollider (getRect()->y, getRect()->x);
            if(collider-> hasCollided("Ground")){
                getRect()->y--;
            }
        }
             if (session.keyDown(SDLK_d)){
            getRect()->x++;
            collider-> updateCollider (getRect()->y, getRect()->x);
            if(collider-> hasCollided("Ground")){
                getRect()->x--;
            }
        }
        collider -> update();
    }
private: 
    Collider2D* collider;
};

class Ground : public Sprite{
    public:
        Ground(int x, int y, int w, int h, std::string txt) 
            : Sprite(x,y,w,h,txt), collider(new Collider2D(x,y,w,h,this,"Ground")){}
    private:
        Collider2D* collider;
};


int main (int argc, char** argv){

   Player* player = new Player(0,0,128,128, "/images/Idle.png", 6, 32);
   Ground* ground = new Ground(250,250,200,200, "/images/bg.jpg");
   session.addComponent(ground);
   session.addComponent(player);
   session.run();

    return 0;
}