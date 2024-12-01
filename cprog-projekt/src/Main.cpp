#include "Session.h"
#include "Sprite.h"
#include "Component.h"
#include <string>
//#include <SDL2/SDL.h>

using namespace engine;

class Player : public Sprite{
public:
    Player(int x, int y, int w, int h, std::string txt, int frames, int xFrame) : Sprite(x, y, w, h, txt, frames, xFrame){}
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
    }
};

int main (int argc, char** argv){

   Player* player = new Player(100,100,128,128, "/images/Idle.png", 6, 32);
   session.addComponent(player);
   session.run();

    return 0;
}