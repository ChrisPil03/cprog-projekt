#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <unordered_map>
#include <string>
#include <SDL2/SDL_mixer.h>

namespace engine
{
    class SoundManager
    {
    public:
        static SoundManager* getInstance();
        void addSound(std::string soundPath, std::string name);
        void playSound(std::string name, bool loop);
        ~SoundManager();

        inline static SoundManager* soundManager = nullptr;
    private:
        SoundManager();

        std::unordered_map<std::string, Mix_Chunk*> sounds;
    };
}

#endif