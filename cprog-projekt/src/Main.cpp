#include "Session.h"
#include "Game_SceneManager.h"
#include "Game_GameManager.h"
#include "SoundManager.h"

int main (int argc, char** argv){
     
    engine::SoundManager* soundM = engine::SoundManager::getInstance();
    soundM->addSound("/sounds/Floating.Wav", "MenuMusic");
    soundM->addSound("/sounds/Falling_120bpm.wav", "LevelMusic");

    game::SceneManager* sm = game::SceneManager::getInstance();

    engine::session.run();
    
    delete sm;

    return 0;
}