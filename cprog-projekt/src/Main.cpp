#include "Session.h"
#include "Game_SceneManager.h"
#include "Game_GameManager.h"

int main (int argc, char** argv){
     
    game::SceneManager* sm = game::SceneManager::getInstance();

    engine::session.run();
    
    delete sm;

    return 0;
}