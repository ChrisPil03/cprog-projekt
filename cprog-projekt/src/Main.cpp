#include "Session.h"
#include "Game_SceneManager.h"
#include "Game_GameManager.h"
#include "SoundManager.h"
#include <iostream>

int main (int argc, char** argv){
     
    engine::SoundManager* soundM = engine::SoundManager::getInstance();
    soundM->addSound("/sounds/Floating.Wav", "MenuMusic");
    soundM->addSound("/sounds/Falling_120bpm.wav", "LevelMusic");

    game::GameManager* gm = game::GameManager::getInstance();
    game::SceneManager* sm = game::SceneManager::getInstance();

    engine::session.run();
    
    std::cout << "After run" << std::endl;

    delete gm;
    delete sm;

    return 0;
}