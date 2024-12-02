#include "Session.h"
#include "Sprite.h"
#include "Component.h"
#include <string>
#include <Collider2D.h>
//#include <SDL2/SDL.h>

using namespace engine;

class Player : public Sprite{
public:
    Player(int x, int y, int w, int h, std::string txt, int frames, int xFrame) : Sprite(x, y, w, h, txt, frames, xFrame), collider(new Collider2D(x,y,32,32,this,"Player")){}
 
    void update(){
        if (session.keyDown(SDLK_w)){
            getRect()->y--;
        }
        if (session.keyDown(SDLK_a)){
            getRect()->x--;
        }
        if (session.keyDown(SDLK_s)){
            getRect()->y++;
        }
        if (session.keyDown(SDLK_d)){
            getRect()->x++;
        }
        if (collider->hasCollided("Ground")){
            if (session.keyDown(SDLK_w)){
                getRect()->y++;
            }
            if (session.keyDown(SDLK_a)){
                getRect()->x++;
            }
            if (session.keyDown(SDLK_s)){
                getRect()->y--;
            }
            if (session.keyDown(SDLK_d)){
                getRect()->x--;
            }            
        }
    }
private: 
    Collider2D* collider;
};

class Ground : public Sprite{
    public:
        Ground(int x, int y, int w, int h, std::string txt) : Sprite(x,y,w,h,txt), collider(new Collider2D(x,y,w,h,this,"Ground")){}
    private:
        Collider2D* collider;
};


int main (int argc, char** argv){

   Player* player = new Player(100,100,128,128, "/images/Idle.png", 6, 32);
   Ground* ground = new Ground(200,200,200,200, "/images/bg.jpg");
   session.addComponent(ground);
   session.addComponent(player);
   session.run();

    return 0;
}