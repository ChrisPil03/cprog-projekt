#include "Session.h"
#include "Sprite.h"
#include "Component.h"
#include <string>
//#include <SDL2/SDL.h>

using namespace engine;

class Player : public Sprite{
public:
    Player(int x, int y, int w, int h, std::string txt) : Sprite(x, y, w, h, txt){}
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

   Player* player = new Player(100,100,100,100, "/images/bg.jpg");
   session.addComponent(player);
   session.run();

    return 0;
}