#include "SoundManager.h"
#include "Constants.h"

namespace engine
{
    SoundManager* SoundManager::getInstance(){
        if (!soundManager){
            return new SoundManager();
        }
        return nullptr;
    }

    SoundManager::SoundManager(){
        if (!soundManager){
            soundManager = this;
        }
    }

    void SoundManager::addSound(std::string soundPath, std::string name){
        sounds[name] = Mix_LoadWAV((constants::gResPath + soundPath).c_str());
    }

    void SoundManager::playSound(std::string name, bool loop){
        // Can only play one sound at a time
        Mix_PlayChannel(0,sounds[name], (loop) ? -1 : 0);
    }

    SoundManager::~SoundManager(){
        for (auto sound : sounds){
            Mix_FreeChunk(sound.second);
        }
        sounds.clear();
    }
}