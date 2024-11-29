#include "Session.h"
#include "Sprite.h"
#include "Component.h"
//#include <SDL2/SDL.h>

using namespace engine;

class Player : public Sprite{
public:
    Player(int x, int y, int w, int h) : Sprite(x, y, w, h){}
    void update(){
        if (session.getKeyDown() == SDLK_w){
            getRect()->y--;
        }
        if (session.getKeyDown() == SDLK_a){
            getRect()->x--;
        }
        if (session.getKeyDown() == SDLK_s){
            getRect()->y++;
        }
        if (session.getKeyDown() == SDLK_d){
            getRect()->x++;
        }
    }
};

int main (int argc, char** argv){

   //Sprite* testSprite = Sprite::getInstance(100, 100, 100, 100);
   Player* player = new Player(100,100,100,100);
   session.addComponent(player);
   //session.addComponent(testSprite);
   session.run();

    return 0;
}